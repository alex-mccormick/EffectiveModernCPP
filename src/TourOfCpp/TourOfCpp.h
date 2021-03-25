#include "../include/stdafx.h"
#include "../Generic/BookChapter.h"

enum class TrafficLight {
    Red=0,
    Yellow,
    Green
};

enum TrafficLightColour {
    Red,
    Amber,
    Green
};

enum class UnionValueType {
    str, num, trafficLight
};

union UnionValue {
    char c;
    int i;
    TrafficLight t;
};

struct MyValueStruct {
    std::string name;
    UnionValueType T;
    UnionValue v;

    void print(void);
};

struct MyVectorStruct {
    double* data;
    int sz;
};

class MyVector
{
    public:
        MyVector(int);
        ~MyVector();
        double& operator[](int);
        int size();

    private:
        double* data;
        int sz;

};

class A2_UserDefinedTypes
    : public BookChapter
{
    public:
        A2_UserDefinedTypes();
        ~A2_UserDefinedTypes();

    private:
        void StructureDemo(void);
        void ClassDemo(void);
        void UnionDemo(void);
        void VariantDemo(void);

};