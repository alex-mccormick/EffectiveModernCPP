#include "TourOfCpp.h"
#include <variant>

A2_UserDefinedTypes::A2_UserDefinedTypes()
    :BookChapter("User Defined Types")
{

    this->menuMap["StructDemo"] = (BookChapter::MenuFunction) &(A2_UserDefinedTypes::StructureDemo);
    this->menuMap["ClassDemo"] = (BookChapter::MenuFunction) &(A2_UserDefinedTypes::ClassDemo);
    this->menuMap["UnionDemo"] = (BookChapter::MenuFunction) &(A2_UserDefinedTypes::UnionDemo);
    this->menuMap["VariantDemo"] = (BookChapter::MenuFunction) &(A2_UserDefinedTypes::VariantDemo);

}

void printMyValueStruct(const MyValueStruct & v)
{
    if (v.T == UnionValueType::str)
        std::cout << "v is char: " << v.v.c << std::endl;
    else if (v.T == UnionValueType::num)
        std::cout << "v is int: " << v.v.i << std::endl;
    else if (v.T == UnionValueType::trafficLight)
        std::cout << "v is ptr: " << static_cast<int>(v.v.t) << std::endl;

    std::cout << std::endl;
}

void initMyVectorStruct(MyVectorStruct & v, int sz)
{
    v.data = new double[sz];
    v.sz = sz;
}
void destructMyVectorStruct(MyVectorStruct & v)
{
    delete v.data;
}

MyVector::MyVector(int s)
    :data{new double[s]}, sz{s}
{
    data[0] = 1;
    data[1] = 5;
    data[2] = 2;
}

MyVector::~MyVector()
{
    delete data;
}

int MyVector::size()
{
    return this->sz;
}

double& MyVector::operator[](int i)
{
    return data[i];
}

void A2_UserDefinedTypes::StructureDemo(void)
{
    MyVectorStruct v;

    initMyVectorStruct(v, 3);
    v.data[0] = 1;
    v.data[1] = 5;
    v.data[2] = 2;

    std::cout << "The structure array now reads: " << std::endl;
    for (auto i = 0; i < v.sz; i++)
    {
        std::cout << v.data[i] << ", ";
    }
    std::cout << std::endl;

    destructMyVectorStruct(v);
}

void A2_UserDefinedTypes::ClassDemo(void)
{
    MyVector v(3);

    v[0] = 1;
    v[1] = 8;
    v[2] = 5;

    std::cout << "The class array now reads: " << std::endl;
    for (auto i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;

}

void A2_UserDefinedTypes::UnionDemo(void)
{
    MyValueStruct s;
    s.name = "Char Struct";
    s.T = UnionValueType::str;
    s.v.c = 'a';
    printMyValueStruct(s);

    s.name = "Int Struct";
    s.T = UnionValueType::num;
    s.v.i = 2;
    printMyValueStruct(s);

    s.name = "TrafficLight Struct";
    s.T = UnionValueType::trafficLight;
    s.v.t = TrafficLight::Green;
    printMyValueStruct(s);
}

template<typename T1, typename T2>
void displayVariant(std::variant<T1, T2> v)
{
    if (std::holds_alternative<int>(v))
    {
        std::cout << "Variant as " << typeid(T1).name() << ": " << std::get<T1>(v) << std::endl;
    }
    else if (std::holds_alternative<TrafficLightColour>(v))
    {
        std::cout << "Variant as " << typeid(T2).name() << ": " << std::get<T2>(v) << std::endl;
    }
}

void A2_UserDefinedTypes::VariantDemo(void)
{
    std::variant<int, TrafficLightColour> variant {2};
    
    displayVariant(variant);

    variant = Amber;
    displayVariant(variant);
}