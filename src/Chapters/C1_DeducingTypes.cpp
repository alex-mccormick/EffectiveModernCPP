#include "Chapters.h"
#include "../Generic/Widget.h"
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <string>
#include <cstdlib>
#include <boost/type_index.hpp>

C1_DeducingTypes::C1_DeducingTypes()
    : BookChapter("DeducingTypes")
{
    this->menuMap["ReferenceAndPointer"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::TypeDeduction);
    this->menuMap["TemplateTypeDeduction"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::TemplateTypeDeduction);
    this->menuMap["AutoTypeDeduction"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::AutoTypeDeduction);
    this->menuMap["ViewTypes"] = (BookChapter::MenuFunction) &(C1_DeducingTypes::ViewTypes);
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
    int x = 27;
    const int cx = x;
    const int& rx = x;

    std::cout << "Deducing type from RValue Reference" << std::endl;
    DeduceTypeFromRValueReference(27);
    DeduceTypeFromRValueReference(x);
    DeduceTypeFromRValueReference(cx);
    DeduceTypeFromRValueReference(rx);

    std::cout << "Deducing type from pass by value" << std::endl;
    DeduceTypeFromPassByValue(27);
    DeduceTypeFromPassByValue(x);
    DeduceTypeFromPassByValue(cx);
    DeduceTypeFromPassByValue(rx);

    int vals[] = {1, 3, 5, 7};
    std::cout << "There are " << C1_DeducingTypes::ArraySize(vals) << " values in the array" << std::endl;
}

auto createInt()
{
    return 1;
}
template<typename T>
auto createRef(T& x)
{
    return x; // Note the warning here: returning the address of a local variable
}
template<typename T>
auto createRValueRef(T&& x)
{
    return x;
}
std::vector<Widget> createVector()
{
    std::vector<Widget> vector;
    vector.push_back(Widget(1, 2));
    vector.push_back(Widget());
    vector.push_back(Widget(1.1, -3.6));

    return vector;
}

void C1_DeducingTypes::AutoTypeDeduction()
{
    auto x = 22;
    const auto cx = x;
    const auto& rx = x;

    std::cout << "Pointers and references" << std::endl;
    std::cout << "T: " << type_name<decltype(22)>() << std::endl;
    std::cout << "T: " << type_name<decltype(x)>() << std::endl;
    std::cout << "T: " << type_name<decltype(cx)>() << std::endl;
    std::cout << "T: " << type_name<decltype(rx)>() << std::endl;

    std::cout << "RValue References" << std::endl;
    auto&& xval = 22;
    auto&& xref = x;
    auto&& cxref = cx;
    auto&& rxref = rx;
    std::cout << "T: " << type_name<decltype(xval)>() << std::endl;
    std::cout << "T: " << type_name<decltype(xref)>() << std::endl;
    std::cout << "T: " << type_name<decltype(cxref)>() << std::endl;
    std::cout << "T: " << type_name<decltype(rxref)>() << std::endl;

    std::cout << "Functions returning auto" << std::endl;
    std::cout << "T: " << type_name<decltype(createInt())>() << std::endl;
    std::cout << "T: " << type_name<decltype(createRef(x))>() << std::endl;
    std::cout << "T: " << type_name<decltype(createRef(rx))>() << std::endl;
    std::cout << "T: " << type_name<decltype(createRValueRef(22))>() << std::endl;
    std::cout << "T: " << type_name<decltype(createRValueRef(x))>() << std::endl;
}

void C1_DeducingTypes::ViewTypes()
{
    auto vector = createVector();
    DeduceTypeFromFunction(&vector[0]);
    DeduceTypeFromStd(&vector[0]); // Note that this is different, and wrong.
    DeduceTypeFromBoost(&vector[0]);

    const auto cvector = createVector();
    DeduceTypeFromFunction(&cvector[0]);
    DeduceTypeFromStd(&cvector[0]);
    DeduceTypeFromBoost(&cvector[0]);
}

template<typename T>
void C1_DeducingTypes::DeduceTypeFromFunction(const T& param)
{
    // std::cout << "T: " << type_name<T>() << std::endl;
    std::cout << "T: " << type_name<T>() << ", param: " << type_name<decltype(param)>() << std::endl;
}
template<typename T>
void C1_DeducingTypes::DeduceTypeFromBoost(const T& param)
{
    // std::cout << "T: " << type_name<T>() << std::endl;
    std::cout << "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << ", param: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}
template<typename T>
void C1_DeducingTypes::DeduceTypeFromStd(const T& param)
{
    // std::cout << "T: " << type_name<T>() << std::endl;
    std::cout << "T: " << typeid(T).name() << ", param: " << typeid(param).name() << std::endl;
}
template<typename T>
void C1_DeducingTypes::DeduceTypeFromRValueReference(T&& param)
{
    // std::cout << "T: " << type_name<T>() << std::endl;
    std::cout << "T: " << type_name<T>() << ", param: " << type_name<decltype(param)>() << std::endl;
}
template<typename T>
void C1_DeducingTypes::DeduceTypeFromPassByValue(T param)
{
    // std::cout << "T: " << type_name<T>() << std::endl;
    std::cout << "T: " << type_name<T>() << ", param: " << type_name<decltype(param)>() << std::endl;
}
template<typename T, std::size_t N>
constexpr std::size_t C1_DeducingTypes::ArraySize(T (&)[N]) noexcept
{
    return N;
}