#include "Chapters.h"
#include <limits>

C2_Auto::C2_Auto()
    : BookChapter("Auto")
{
    this->menuMap["BoolArray"] = (BookChapter::MenuFunction) &(C2_Auto::BoolArray);
    this->menuMap["ExplicitInitialiser"] = (BookChapter::MenuFunction) &(C2_Auto::ExplicitInitialiser);
    this->menuMap["MutexDemo"] = (BookChapter::MenuFunction) &(C2_Auto::MutexDemo);
}

void C2_Auto::BoolArray()
{
    std::vector<int> integer_vector {1, 2, 3, 5};
    std::vector<bool> bool_vector {false, false, true, true};

    // The integer [] operator will return int&, so we can do:
    std::cout << "The second value in the integer vector is currently: " << integer_vector[1] << std::endl;
    auto& ref_int = integer_vector[1];
    ref_int = 10;
    std::cout << "The local variable now has value " << ref_int << std::endl;
    std::cout << "The second value in the integer vector is currently: " << integer_vector[1] << ", expected 10" << std::endl;

    // The bool [] operator does not return bool&, but it looks a lot like it
    std::cout << "The second value in the boolean vector is currently: " << (bool_vector[1] ? "true" : "false") << std::endl;
    bool ref_bool = bool_vector[1];
    ref_bool = true;
    std::cout << "The local variable now has value " << (ref_bool ? "true" : "false") << std::endl;
    std::cout << "The second value in the boolean vector is currently: " << (bool_vector[1] ? "true" : "false") << ", expected false" << std::endl;

    // We cannot use auto in the same way
    std::cout << "The third value in the boolean vector is currently: " << (bool_vector[2] ? "true" : "false") << std::endl;
    auto auto_ref_bool = bool_vector[2];
    auto_ref_bool = false;
    std::cout << "The local variable now has value " << (auto_ref_bool ? "true" : "false") << std::endl;
    std::cout << "The third value in the boolean vector is currently: " << (bool_vector[2] ? "true" : "false") << ", this is undefined behaviour" << std::endl;
   
    // The type of auto_ref_bool is not logical:
    std::cout << "auto_ref_bool is a " << typeid(auto_ref_bool).name() << std::endl;
}

double getSmallNumber()
{
    return (std::numeric_limits<float>::min() * 1.0e-10);
}

void C2_Auto::ExplicitInitialiser()
{
    // Sometimes, auto deduces an unfavourable type
    auto smallNumberReturned = getSmallNumber();
    std::cout << "The small number returned by auto is " << static_cast<double>(smallNumberReturned) << std::endl;
    float smallFloatReturned = getSmallNumber(); // Compiles, but not obvious that this is a narrowing conversion which will cost precision
    std::cout << "The small number returned by float is " << static_cast<double>(smallFloatReturned) << std::endl;
    auto smallDoubleExplicitlyReturned = static_cast<double>(getSmallNumber()); // Compiles, but not obvious that this is a narrowing conversion which will cost precision
    std::cout << "The small number returned by explicit initialisation is " << static_cast<double>(smallDoubleExplicitlyReturned) << std::endl;
}

namespace MutexExample {

    static std::mutex quadM, radM, popM;

    int quadrant(std::shared_ptr<Widget> pw) {
        return (pw ? pw->GetQuadrant() : 0);
    };
    double radius(std::unique_ptr<Widget> pw) {
        return (pw ? pw->GetRadius() : 0);
    };
    bool populated(Widget* pw) {
        return (pw && pw->IsPopulated());
    }

    template<typename FuncType,
             typename MuxType,
             typename PtrType>
    decltype(auto) lock_and_call(FuncType func, MuxType& mutex, PtrType&& ptr) {
        std::lock_guard<std::mutex> g(mutex);
        return func(std::move(ptr));
    };
};

void C2_Auto::MutexDemo()
{
    auto shared_pw = std::make_shared<Widget>(-3.0, 4.0);
    auto unique_pw = std::make_unique<Widget>(5.0, 12.0);
    auto raw_pw = new Widget(1.0, -2.0);

    auto quad_up = unique_pw->GetQuadrant();
    auto quad_rp = raw_pw->GetQuadrant();
    
    auto quad_sp = MutexExample::lock_and_call(MutexExample::quadrant, MutexExample::quadM, shared_pw);
    auto rad = MutexExample::lock_and_call(MutexExample::radius, MutexExample::radM, std::move(unique_pw)); // Can't copy a unique ptr
    auto pop = MutexExample::lock_and_call(MutexExample::populated, MutexExample::popM, raw_pw);

    // Compile ok, but segfault on null call
    auto nullptr_quad = MutexExample::lock_and_call(MutexExample::quadrant, MutexExample::quadM, nullptr);
    auto nullptr_rad = MutexExample::lock_and_call(MutexExample::radius, MutexExample::radM, nullptr);
    auto nullptr_pop = MutexExample::lock_and_call(MutexExample::populated, MutexExample::popM, nullptr);

    // auto zero_quad = MutexExample::lock_and_call(MutexExample::quadrant, MutexExample::quadM, 0); // Error: not a pointer type

    delete raw_pw;
}