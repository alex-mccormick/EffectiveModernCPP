#include "Chapters.h"

C4_SmartPointers::C4_SmartPointers()
    : BookChapter("SmartPointers") {
    this->menuMap["ResourceOwnership"] = (BookChapter::MenuFunction) &(C4_SmartPointers::ResourceOwnership);
}

void C4_SmartPointers::ResourceOwnership() {
    
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
        auto u_ptr_d1 = shape_factory_with_deleter(ShapeType::Face, new Widget(1,1), new Widget(2,2));
        auto u_ptr_d2 = shape_factory_with_deleter(ShapeType::Face);
        std::cout << "The size of a unique pointer with a custom deleter is " << sizeof(u_ptr_d2) << std::endl;
        std::cout << "Destroy the face by ending the scope" << std::endl;
    }

    // To generate a shared pointer... we just explicitly assign it
    {
        std::cout << "Make a shared pointer to a circle" << std::endl;
        std::shared_ptr<Circle> s_ptr = shape_factory(ShapeType::Circle);
        std::cout << "The size of a shared pointer is " << sizeof(s_ptr) << std::endl;
    }
    // A shared pointer can have a deleter, but it does not influence the type
    {
        // TODO: write some custom deleters of different types for these functions and prove that an array works (p126)
        std::cout << "Make a shared pointer to a circle" << std::endl;
        std::shared_ptr<Circle> s_ptr = shape_factory(ShapeType::Circle);
        std::cout << "The size of a shared pointer is " << sizeof(s_ptr) << std::endl;
    }



}