#include "Chapters.h"
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <string>
#include <cstdlib>

C1_DeducingTypes::C1_DeducingTypes()
    : BookChapter("DeducingTypes")
{
    this->menuMap["ReferenceAndPointer"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::TypeDeduction);
    this->menuMap["TemplateTypeDeduction"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::TemplateTypeDeduction);
    this->menuMap["AutoTypeDeduction"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::AutoTypeDeduction);
    this->menuMap["AutoInLambdas"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::AutoInLambda);
}


C1_DeducingTypes::~C1_DeducingTypes()
{
    
}


template <class T>
std::string type_name(T param)
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

template <class T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

void C1_DeducingTypes::TypeDeduction()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    
    DeduceTypeFromFunction(x);
    DeduceTypeFromFunction(cx);
    DeduceTypeFromFunction(&cx);
    DeduceTypeFromFunction(rx);
    DeduceTypeFromFunction(&rx);

}

void C1_DeducingTypes::TemplateTypeDeduction()
{
}

void C1_DeducingTypes::AutoTypeDeduction()
{
}

void C1_DeducingTypes::AutoInLambda()
{
}

template<typename T>
void C1_DeducingTypes::DeduceTypeFromFunction(const T& param)
{
    std::cout << "T: " << type_name<T>() << std::endl;
    // std::cout << "T: " << type_name<T>() << ", param: " << type_name(param) << std::endl;
}
template<typename T>
void C1_DeducingTypes::DeduceTypeFromRValueReference(T&& param)
{
    std::cout << "T: " << type_name<T>() << std::endl;
    // std::cout << "T: " << type_name<T>() << ", param: " << type_name(param) << std::endl;
}
