#include "Chapters.h"
#include "../Generic/Widget.h"
#include <thread>

C4a_SmartPointers::C4a_SmartPointers()
    : BookChapter("SmartPointers") {
    this->menuMap["ResourceOwnership"] = (BookChapter::MenuFunction) &(C4a_SmartPointers::ResourceOwnership);
    this->menuMap["CuriousRecurringTemplatePattern"] = (BookChapter::MenuFunction) &(C4a_SmartPointers::CRTP);
    this->menuMap["WeakPtr"] = (BookChapter::MenuFunction) &(C4a_SmartPointers::WeakPtr);
}

void C4a_SmartPointers::ResourceOwnership() {
    
    Overriding::Shape::ShapesLeft = 0;
    std::cout << "Use unique-ptr for exclusive-ownership" << std::endl;

    // Factory functions can (should) return unique_ptr
    {
        std::cout << "Make a shape within this scope" << std::endl;
        auto u_ptr = shape_factory(ShapeType::Shape);
        std::cout << "The size of a unique pointer with a default deleter is " << sizeof(u_ptr) << std::endl;
        std::cout << "Destroy the shape by ending the scope" << std::endl;
    }

    // A custom deleter can be specified
    {
        std::cout << "Make a face within this scope" << std::endl;
        auto u_ptr_d1 = shape_factory_with_deleter(ShapeType::Face, new ExWidget(1,1), new ExWidget(2,2));
        auto u_ptr_d2 = shape_factory_with_deleter(ShapeType::Face);
        std::cout << "The size of a unique pointer with a custom deleter is " << sizeof(u_ptr_d2) << std::endl;
        std::cout << "Destroy the face by ending the scope" << std::endl;
    }

    // To generate a shared pointer... we just explicitly assign it
    {
        std::cout << "Make a shared pointer to a circle" << std::endl;
        std::shared_ptr<Overriding::Shape> s_ptr = shape_factory(ShapeType::Circle);
        std::cout << "The size of a shared pointer is " << sizeof(s_ptr) << std::endl;
    }
    // A shared pointer can have a deleter, but it does not influence the type
    {
        std::cout << "Unique and shared pointers to different types of pointers" << std::endl;

        // Return a unique pointer from the factory function
        auto u_ptr1 = shape_factory_with_deleter(ShapeType::Face);
        auto u_ptr2 = shape_factory_with_returning_deleter(ShapeType::Face);

        std::cout << "Create a shared pointer by moving the unique ptr" << std::endl;
        std::shared_ptr<Overriding::Shape> s_ptr1(std::move(u_ptr1));
        std::shared_ptr<Overriding::Shape> s_ptr2(std::move(u_ptr2));

        std::cout << "Implicitly create (this is just the move constructor)" << std::endl;
        std::shared_ptr<Overriding::Shape> s_ptr3 = shape_factory_with_deleter(ShapeType::Face);
        std::shared_ptr<Overriding::Shape> s_ptr4 = shape_factory_with_returning_deleter(ShapeType::Face);

        std::cout << "We can also just make_shared" << std::endl;
        // These don't have the custom deleter
        auto s_ptr5 = std::make_shared<Overriding::Face>(new ExWidget(-4, -3), new ExWidget(-2, -1));
        auto s_ptr6 = std::make_shared<Overriding::Face>();

        // We cannot put the unique ptrs in an array, because they are not of the same type
        // You get a really ugly warning message here
        // {
        //     std::cout << "Set up an array of unique ptrs" << std::endl;
        //     auto u_ptr_vec = std::vector<std::unique_ptr<Overriding::Shape>>();
        //     u_ptr_vec.emplace_back(u_ptr1);
        //     u_ptr_vec.emplace_back(u_ptr2);
        // }

        {
            std::cout << "Set up an array of shared ptrs" << std::endl;
            auto s_ptr_vec = std::vector<std::shared_ptr<Overriding::Shape>>();
            s_ptr_vec.emplace_back(s_ptr1);
            s_ptr_vec.emplace_back(s_ptr2);
            s_ptr_vec.emplace_back(s_ptr3);
            s_ptr_vec.emplace_back(s_ptr4);
            s_ptr_vec.emplace_back(s_ptr5);
            s_ptr_vec.emplace_back(s_ptr6);

            // All four of these options are now deleted using the custom deleter, because the shared_ptr has carried this information through
        }

    }
}

void C4a_SmartPointers::CRTP() {
    

    // If you want to add shared ptr to "this", this requires a special implementation in the base class
    std::cout << "This is the correct implementation" << std::endl;
    auto pWidget1 = std::make_shared<ExWidget>(2, 3);
    std::shared_ptr<ExWidget> pWidget2{pWidget1};

    {
        // Within this scope, we're going to do some widget processing, then delete the widgets
        // Using shared_from_this prevents generation of a new control block
        std::vector<std::shared_ptr<ExWidget>> processedWidgets;

        pWidget1->ProcessWidget(2, processedWidgets);

        // Process this widget again...
        pWidget1->ProcessWidget(0.5, processedWidgets);
        std::cout << "The first processed widget is " << processedWidgets[0]->get_x()  << std::endl;
    }

    // The shared pointers have gone, but we should still be able to access pWidget1
    std::cout << "pWidget1 has value: " << pWidget1->get_x() << std::endl;

    std::cout << "Now we'll just lazily add \"this\" to the back of the vector" << std::endl;
    // If you want to add shared ptr to "this", this implementation is wrong
    {
        // Within this scope, we're going to do some widget processing but return a pointer to 'this', not to shared_from_this
        // This produces a new control block, and all hell breaks loose
        std::vector<std::shared_ptr<ExWidget>> processedWidgets;

        pWidget2->ProcessWidget(2, processedWidgets); // This one works
        // pWidget2->ProcessWidgetWithThis(2, processedExWidgets); // This one fails
        std::cout << "The first processed widget is " << processedWidgets[0]->get_x() << std::endl;
    }
    // And now we just deleted something that we need to be in scope, so it fails
    std::cout << "pWidget2 has value: " << pWidget2->get_x() << std::endl;


}

constexpr int nWidgets = 10000;

void double_widgets(std::vector<std::weak_ptr<ExWidget>>& widgets, std::vector<std::shared_ptr<ExWidget>>* doubledWidgets)
{
    // We can only double the widget if it doesn't dangle
    // So we need to lock the shared ptr
    for (int i = 0; i != nWidgets; ++i)
    {
        std::shared_ptr<ExWidget> spw = widgets[i].lock();
        if (spw)
        {
            // We only get here if it's not null, and therefore still exists
            spw->get_x() *= 2;
            spw->get_y() *= 2;
            if (doubledWidgets)
            {
                doubledWidgets->push_back(spw);
            }
        }
        // At this point, spw goes out of scope and is implicitly unlocked
    }

}

void delete_widgets(std::vector<std::shared_ptr<ExWidget>>& widgets)
{
    auto pLast = widgets.end();
    for (int i = 0; i != nWidgets; ++i)
    {
        std::advance(pLast, -1);
        widgets.erase(pLast);
    }
}

void C4a_SmartPointers::WeakPtr() {

    // Weak ptrs are generated by locking a shared ptr, so that it can't be accessed elsewhere
    
    // Note you can't dereference a weakptr

    std::vector<std::shared_ptr<ExWidget>> s_widgets;
    std::vector<std::weak_ptr<ExWidget>> widgets;
    widgets.reserve(nWidgets);
    for (int i = 0; i != nWidgets; ++i)
    {
        auto s_ptr = std::make_shared<ExWidget>(1, i);
        s_widgets.push_back(s_ptr);
        auto w_ptr = std::weak_ptr(s_ptr);
        widgets.push_back(w_ptr);
    }

    // Build two threads
    //     One deletes the widgets in reverse order
    //     One doubles the widgets in forwards order

    std::unique_ptr<std::vector<std::shared_ptr<ExWidget>>> doubledWidgets = std::make_unique<std::vector<std::shared_ptr<ExWidget>>>();

    std::thread t_double {double_widgets, std::ref(widgets), doubledWidgets.get()};

    // Note that we are deleting the original shared_ptrs
    // The weak ptrs are "just" wrappers of the object, and so passing the weak ptrs here means the objects never actually exist in the first place
    std::thread t_delete {delete_widgets, std::ref(s_widgets)};


    t_double.join();
    t_delete.join();

    std::cout << "After our deliberately engineered race condition, we successfully doubled " << doubledWidgets->size() << " widgets" << std::endl;
    std::cout << "The list of widgets contains " << s_widgets.size() << " widgets" << std::endl;

}