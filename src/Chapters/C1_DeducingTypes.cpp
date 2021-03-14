#include "Chapters.h"

C1_DeducingTypes::C1_DeducingTypes()
    : BookChapter("DeducingTypes")
{
    this->menuMap["ReferenceAndPointer"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::TypeDeduction);
}


C1_DeducingTypes::~C1_DeducingTypes()
{
    
}

void C1_DeducingTypes::TypeDeduction()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    
    DeduceTypeFromFunction(x);
    DeduceTypeFromFunction(cx);
    DeduceTypeFromFunction(rx);

}

template<typename T>
void C1_DeducingTypes::DeduceTypeFromFunction(T& param)
{
    std::cout << "T: " << typeid(T).name() << std::endl;
}