#include "Chapters.h"
#include <limits>

C2_Auto::C2_Auto()
    : BookChapter("Auto")
{
    this->menuMap["BoolArray"] = (BookChapter::MenuFunction) &(C2_Auto::BoolArray);
    this->menuMap["ExplicitInitialiser"] = (BookChapter::MenuFunction) &(C2_Auto::ExplicitInitialiser);
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
