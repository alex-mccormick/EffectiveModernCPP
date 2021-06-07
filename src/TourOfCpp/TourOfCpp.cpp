#include "TourOfCpp.h"
#include "Matrix.h"
#include "MyVector.tpp"
#include "SimpleCollection.h"
#include <variant>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include <ctime>
#include <chrono>
#include <string>

using namespace std::string_literals; // enables s-suffix for std::string literals
using namespace std::literals::string_view_literals; // enables s-suffix for std::string literals

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

void initSimpleVectorStruct(SimpleVectorStruct & v, int sz)
{
    v.data = new double[sz];
    v.sz = sz;
}
void destructSimpleVectorStruct(SimpleVectorStruct & v)
{
    delete v.data;
}

SimpleVector::SimpleVector(int s)
    :data{new double[s]}, sz{s}
{
    data[0] = 1;
    data[1] = 5;
    data[2] = 2;
}

SimpleVector::~SimpleVector()
{
    delete data;
}

int SimpleVector::size()
{
    return this->sz;
}

double& SimpleVector::operator[](int i)
{
    return data[i];
}

void A2_UserDefinedTypes::StructureDemo(void)
{
    SimpleVectorStruct v;

    initSimpleVectorStruct(v, 3);
    v.data[0] = 1;
    v.data[1] = 5;
    v.data[2] = 2;

    std::cout << "The structure array now reads: " << std::endl;
    for (auto i = 0; i < v.sz; i++)
    {
        std::cout << v.data[i] << ", ";
    }
    std::cout << std::endl;

    destructSimpleVectorStruct(v);
}

void A2_UserDefinedTypes::ClassDemo(void)
{
    SimpleVector v(3);

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


A3_Modularity::A3_Modularity()
    :BookChapter("Modularity")
{

    this->menuMap["Matrix"] = (BookChapter::MenuFunction) &(A3_Modularity::MatrixDemo);

}

void A3_Modularity::MatrixDemo()
{
    Matrix m1{2, 0.0};
    Matrix m2{2, 1.0};

    auto sum = m1+m2;
    std::cout << "m1" << std::endl << m1 << std::endl << std::endl;
    std::cout << "m2" << std::endl << m2 << std::endl << std::endl;
    std::cout << "sum" << std::endl << sum << std::endl << std::endl;

    Matrix bigMatrix{5, 2.4};

    std::cout << "bigMatrix" << std::endl << bigMatrix << std::endl << std::endl;
    try
    {
        auto bigsum = m1 + bigMatrix;
    }
    catch (std::out_of_range& )
    {
        std::cout << "Out of range exception" << std::endl;
        std::cout << "Don't worry, we expected this" << std::endl;
    }
}

A4_Classes::A4_Classes()
    :BookChapter("Classes")
{
    this->menuMap["AbstractClassDemo"] = (BookChapter::MenuFunction) &(A4_Classes::AbstractClassDemo);
    this->menuMap["UniquePtrDemo"] = (BookChapter::MenuFunction) &(A4_Classes::UniquePtrDemo);
}

A4_Classes::~A4_Classes()
{

}

void A4_Classes::AbstractClassDemo()
{
    auto boeing = new Boeing747(1e5);
    auto F35 = new LockheedF35(5e4);
    auto roadCar = new RoadVehicle(4, 4, 1.2);
    auto f1Car = new F1Car(4, 2.5);

    // How fast do they go
    std::cout << "The boeing 747 goes " << boeing->Sound() << " as it goes past, travelling at " << boeing->Speed() << " m/s" << std::endl;
    std::cout << "The F35 goes " << F35->Sound() << " as it goes past, travelling at " << F35->Speed() << " m/s" << std::endl;
    std::cout << "The road car goes " << roadCar->Sound() << " as it goes past, travelling at " << roadCar->Speed() << " m/s" << std::endl;
    std::cout << "The F1 car goes " << f1Car->Sound() << " as it goes past, travelling at " << f1Car->Speed() << " m/s" << std::endl;

    delete boeing;
    delete F35;
    delete roadCar;
    delete f1Car;
}

double GetDuration(double t1, double t2)
{
    return (t2 - t1) / (double)(CLOCKS_PER_SEC);
}

struct TimerStruct
{
    std::chrono::high_resolution_clock::time_point start;

    TimerStruct()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~TimerStruct()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        std::cout << "Timer says " << totalTime.count() * 1000 << " ms" << std::endl;
    } 
};

void A4_Classes::UniquePtrDemo()
{
    auto nPlanes = 100000;

    {
        std::clock_t t1 = std::clock();
        std::vector<AirVehicle*> planes(nPlanes);
        for (auto &p:planes)
        {
            p = new Boeing747{1e5};
        }
        std::clock_t t2 = std::clock();
        std::cout << "Allocating " << nPlanes << " planes to a MyVector without using unique_ptr " << GetDuration(t1, t2) << " s" << std::endl;
        std::cout << "We can prove here that the engines are not cleaned up when the MyVector goes out of scope" << std::endl;
    }

    {
        auto t = TimerStruct();
        std::clock_t t1 = std::clock();
        std::vector<std::unique_ptr<AirVehicle>> planes(nPlanes);
        for (auto &p:planes)
        {
            auto ptr = std::make_unique<Boeing747>(1e5);
            p = std::move(ptr);
        }
        std::clock_t t2 = std::clock();
        std::cout << "Allocating " << nPlanes << " planes to a MyVector by move assignment took " << GetDuration(t1, t2) << " s" << std::endl;
    }

    {
        auto t = TimerStruct();
        std::clock_t t1 = std::clock();
        std::vector<std::unique_ptr<AirVehicle>> planes(nPlanes);
        for (auto i = 0; i != nPlanes; ++i)
        {
            planes.push_back(std::make_unique<Boeing747>(1e5));
        }
        std::clock_t t2 = std::clock();
        std::cout << "Allocating " << nPlanes << " planes to a MyVector by pushing pointers to the back without reserve " << GetDuration(t1, t2)  << " s" << std::endl;
    }

    {        
        auto t = TimerStruct();
        std::clock_t t1 = std::clock();
        std::vector<std::unique_ptr<AirVehicle>> planes(nPlanes);
        planes.reserve(nPlanes);
        for (auto i = 0; i != nPlanes; ++i)
        {
            planes.push_back(std::make_unique<Boeing747>(1e5));
        }
        std::clock_t t2 = std::clock();
        std::cout << "Allocating " << nPlanes << " planes to a MyVector by pushing pointers to the back with reserve " << GetDuration(t1, t2)  << " s" << std::endl;
    }
}

A5_MoveAndCopy::A5_MoveAndCopy()
    :BookChapter("Classes")
{
    this->menuMap["SumMatrixDemo"] = (BookChapter::MenuFunction) &(A5_MoveAndCopy::SumMatrixDemo);
}

A5_MoveAndCopy::~A5_MoveAndCopy()
{

}

void A5_MoveAndCopy::SumMatrixDemo()
{
    // This should be a 2x2 matrix full of zeros
    Matrix m1{2};
    std::cout << "This should be a 2x2 matrix full of zeros" << std::endl;
    std::cout << m1 << std::endl;

    // This should be a 1x1 matrix with the value 2.0
    Matrix m2{2.0};
    std::cout << "This should be a 1x1 matrix with the value 2.0" << std::endl;
    std::cout << m2 << std::endl;

    // Let's make some bigger matrices
    Matrix bigM1(1000, 1.2);
    Matrix bigM2(2000, 1.5);
    Matrix bigM3 = Matrix(3000, 1.8); // The copy should be elided here

    std::cout << "The sizes should be 1000, 2000, 3000" << std::endl;
    std::cout << "Size of bigM1: " << bigM1.size() << std::endl;
    std::cout << "Size of bigM2: " << bigM2.size() << std::endl;
    std::cout << "Size of bigM3: " << bigM3.size() << std::endl;

    // This should use the copy; so now M3 should be the same size as M1 and M1 should still be useable
    bigM3 = bigM1;
    std::cout << "M3 should be the same size as M1" << std::endl;
    std::cout << "Size of bigM1: " << bigM1.size() << std::endl;
    std::cout << "Size of bigM3: " << bigM3.size() << std::endl;

    auto bigMSum = bigM1 + bigM3;
    // Check that an element in the middle of this array is used properly
    std::cout << "We should be able to reference a value in the middle of the matrix, and see that its value is 2.4" << std::endl;
    std::cout << "Element 50 is " << bigMSum[50] << std::endl;

    // Now we want to exercise the move constructor
    bigM2 = std::move(bigM1);
    // Now we have removed any values from m1
    // Check:
    std::cout << "bigM1 is " << (bigM1.isEmpty() ? "empty" : "not empty") << std::endl;
    
}

A6_Templates::A6_Templates()
    :BookChapter("Templates")
{
    this->menuMap["IteratorDemo"] = (BookChapter::MenuFunction) &(A6_Templates::IteratorDemo);
    this->menuMap["MyVectorTemplate"] = (BookChapter::MenuFunction) &(A6_Templates::MyVectorTemplateDemo);
    this->menuMap["FunctionDemo"] = (BookChapter::MenuFunction) &(A6_Templates::FunctionDemo);
    this->menuMap["LambdaDemo"] = (BookChapter::MenuFunction) &(A6_Templates::LambdaDemo);
    this->menuMap["AliasDemo"] = (BookChapter::MenuFunction) &(A6_Templates::AliasDemo);
}

void A6_Templates::IteratorDemo()
{
    Matrix m{5, 3.4};
    std::cout << "The total of all elements in the matrix is " << m.sum() << std::endl;
}

void A6_Templates::MyVectorTemplateDemo()
{
    {
        auto c1 = SimpleCollection(1.2, 2.3);
        std::cout << "a: " << c1.GetA() << ", b: " << c1.GetB() << std::endl;
    }
    {
        SimpleTemplateCollection<std::string> c2 ("Hello"s, "World"s);
        std::cout << "a: " << c2.GetA() << ", b: " << c2.GetB() << std::endl;
    }
    {
        // Test the different ways of setting up a MyVector
        MyVector<double> v1; // Empty
        std::cout << std::endl << "v1: " << v1 << std::endl;
    }
    {
        MyVector<double> v4(4, 1.2); // Length 4, all values 1.2
        std::cout << std::endl << "v4: " << v4 << std::endl;
        std::cout << "The sum of the elements in v4 is " << v4.sum() << std::endl;
    }
    {
        auto v5 = MyVector<double>{5.0, 4.0, 3.0, 1.0, 2.0}; // Initialiser list constructor
        std::cout << std::endl << "v5: " << v5 << std::endl;
        std::cout << "The sum of the elements in v5 is " << v5.sum() << std::endl;

        MyVector<double> v6(v5.begin(), v5.begin()+3); // Iterator constructor
        std::cout << std::endl << "v6: " << v6 << std::endl;
        std::cout << "Iterator constructor: should contain the first two elements of v5"<< std::endl;
        std::cout << "The sum of the elements in v6 is " << v6.sum() << std::endl;

        MyVector<double> v7(v6); 
        std::cout << std::endl << "v7: " << v7 << std::endl;
        std::cout << "Copy constructor from v6, should only have two elements"<< std::endl;
        std::cout << "The sum of the elements in v7 is " << v7.sum() << std::endl;

        MyVector<double> v8{std::move(v7)}; // Move constructor
        std::cout << std::endl << "v8: " << v8 << std::endl;
        std::cout << "Move constructor from v7, v7 should now be empty"<< std::endl;
        std::cout << std::endl << "v7: " << v7 << std::endl;

        auto v9 = MyVector<double>{v8}; // Copy constructor
        std::cout << std::endl << "v9: " << v9 << std::endl;
        std::cout << "Copy constructor from v8, v8 should still be populated" << std::endl;
        std::cout << std::endl << "v8: " << v8 << std::endl;
    }
    {
        auto v10 = MyVector<double>{5.0, 4.0, 3.0, 1.0, 2.0}; // Initialiser list constructor
        std::cout << std::endl << "v10: " << v10 << std::endl;
        v10.append(-10);
        std::cout << std::endl << "v10: " << v10 << std::endl;
    }

}

template<typename Sequence, typename Value>
Value sum(const Sequence& s, Value v)
{
    for (const auto& x : *s)
    {
        v += x;
    }
    return v;
}

void A6_Templates::FunctionDemo()
{
    MyVector v{1.0, 2.2, 4.3, 3.1};
    auto vectorSum = v.sum();
    auto templateSum = sum(&v, 0.0);
    auto templateSumIntegerStart = sum(&v, 0);
    auto templateSumForceArgs = sum<MyVector<double>*, double>(&v, 0);

    std::cout << "Defined a vector v: " << v << std::endl;
    std::cout << "The vector thinks it sum is " << vectorSum << std::endl;
    std::cout << "The template sum function gives " << templateSum << std::endl;
    std::cout << "If we sum with a starting integer, we get " << templateSumIntegerStart << std::endl;
    std::cout << "Or... we could force a double: " << templateSumForceArgs << std::endl;

    LessThan isNegative{0.0};
    LessThan isSmall {10};

    auto bNegative1 = isNegative(-1);
    auto bNegative2 = isNegative(1);
    std::cout << "We have established that -1 " << (bNegative1 ? "is" : "is not") << " negative" << std::endl;
    std::cout << "We have established that 1 " << (bNegative2 ? "is" : "is not") << " negative" << std::endl;

    BitChecker lastBit{1};
    BitChecker penultimateBit{2};

    auto bLastBitTrue3 = lastBit(3);
    auto bPenultimateBitTrue3 = penultimateBit(3);
    auto bLastBitTrue5 = lastBit(5);
    auto bPenultimateBitTrue5 = penultimateBit(5);

    std::cout << "The last bit of 3 is " << bLastBitTrue3 << std::endl;
    std::cout << "The penultimate bit of 3 is " << bPenultimateBitTrue3 << std::endl;
    std::cout << "The last bit of 5 is " << bLastBitTrue5 << std::endl;
    std::cout << "The penultimate bit of 5 is " << bPenultimateBitTrue5 << std::endl;
}

template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& x:c)
        if (pred(x))
            ++cnt;
    
    return cnt;
}

bool lessThanZeroLocalFunction(int x)
{
    return x < 0;
}

void A6_Templates::LambdaDemo()
{
    MyVector v{-1, 1, 2, -5, 3, -4, 1, 0};
    std::cout << "Defined a vector v: " << v << std::endl;

    LessThan isNegative{0.0};
    auto countNegative = count(v, isNegative);
    std::cout << "According to the functor, v contains " << countNegative << " negative numbers" << std::endl;

    auto countNegativeLambda = count(v, [](int x){ return x < 0; });
    std::cout << "According to the lambda, v contains " << countNegativeLambda << " negative numbers" << std::endl;

    // Define the lambda externally
    auto lessThanLambda = [](auto a){ return a < 0; };
    auto countNegativeLambdaVariable = count(v, lessThanLambda);
    std::cout << "According to the pre-defined lambda, v contains " << countNegativeLambdaVariable << " negative numbers" << std::endl;

    // Can't do this
    // bool lessThanExplicitLambda(int) = [&](int x){return x <= breakPoint;};

    int breakPoint = 0;
    // Passing by value here captures the value at the time - it will stay zero
    auto lessThanBreakpointRef = [&](auto a){ return a < breakPoint; };
    auto lessThanBreakpointVal = [=](auto b){ return b < breakPoint; };
    auto countLessThanBreakpointRef1 = count(v, lessThanBreakpointRef);
    auto countLessThanBreakpointVal1 = count(v, lessThanBreakpointVal);
    std::cout << "v contains " << countLessThanBreakpointRef1 << " values less than " << breakPoint << " (by ref)" << std::endl;
    std::cout << "v contains " << countLessThanBreakpointVal1 << " values less than " << breakPoint << " (by val)" << std::endl;

    breakPoint = 4;

    auto countLessThanBreakpointRef2 = count(v, lessThanBreakpointRef);
    auto countLessThanBreakpointVal2 = count(v, lessThanBreakpointVal);
    std::cout << "v contains " << countLessThanBreakpointRef2 << " values less than " << breakPoint << " (by ref)" << std::endl;
    std::cout << "v contains " << countLessThanBreakpointVal2 << " values less than " << breakPoint << " (by val)" << std::endl;

    // This can also be implemented using a function pointer
    auto countLessThanZeroLocalFunction = count(v, lessThanZeroLocalFunction);
    std::cout << "According the local function, v contains " << countLessThanZeroLocalFunction << " negative numbers" << std::endl;

}

void A6_Templates::AliasDemo()
{
    auto keys = MyVector<int>{5, 4, 3, 2, 1};
    auto values = MyVector<double>{5.0, 4.0, 3.0, 1.0, 2.0};

    auto map = MyMap<int,double>(std::move(keys), std::move(values));

    std::cout << "I found a value in my map! At location 4, the value is " << map[4] << std::endl;
    map[2] = -2;
    std::cout << "I changed a value in my map! At location 2, the value is now " << map[2] << std::endl;

    map.Add(10, 15.4);
    std::cout << "I added a value to my map! At location 10, the value is " << map[10] << std::endl;

    std::cout << "I can print the whole map" << std::endl;
    for (auto [k, v] : map)
    {
        std::cout << "The value at " << k << " is " << v << std::endl;
    }

    // String keys
    // Also using copy constructor: note it doesn't make a difference
    const auto strkeys = MyVector{"a"s, "b"s, "d"s, "f"s, "k"s};
    const auto strvalues = MyVector{5.0, 4.0, 3.0, 1.0, 2.0};
    auto stringMap = MyMap(strkeys, strvalues);

    stringMap.Add("new"s, 42);
    std::cout << "I added a value to my map! At location \"new\", the value is " << stringMap["new"s] << std::endl;
    std::cout << "I can print the whole map" << std::endl;
    for (auto [k, v] : stringMap)
    {
        std::cout << "The value at " << k << " is " << v << std::endl;
    }

    // Aliassed type
    const auto intValues = MyVector<double>{1, 2, 3, 4, 6}; // Values are traditionally ints, but we want a double map
    auto doubleMap = MyDoubleMap<std::string>(strkeys, intValues);
    doubleMap.print();

}

void printVariadic() {};
template<typename T, typename... Tail>
void printVariadic(T head, Tail... tail)
{
    std::cout << head << '\t';
    printVariadic(tail...);
}

template<typename T, typename... Tail>
void printVariadicRecurse(T head, Tail... tail)
{
    std::cout << head << '\t';
    // Use constexpr to prevent the code from ever even being generated
    // We will never need to call this function with fewer than 1 parameters
    if constexpr(sizeof...(tail) > 0)
        printVariadicRecurse(tail...);
    else
        std::cout << '\n';
}

template<typename... T>
double sumPack(T... v)
{
    return (v + ... + 0.0);
}

template<typename T, typename... Args>
std::vector<T> generateVector(T first, Args... v)
{
    std::vector<T> initVector{first};
    if constexpr(sizeof...(v) > 0)
    {
        auto laterVector = generateVector(v...);
        initVector.insert(initVector.end(), laterVector.begin(), laterVector.end());
    }

    return initVector;
}

template<typename ...T>
void printFold(T&&... args)
{
    (std::cout << ... << args) << '\n';
}

A7_Concepts::A7_Concepts()
    :BookChapter("Concepts")
{
    this->menuMap["VariadicTemplateDemo"] = (BookChapter::MenuFunction) &(A7_Concepts::VariadicTemplateDemo);
    this->menuMap["FoldDemo"] = (BookChapter::MenuFunction) &(A7_Concepts::FoldDemo);
    this->menuMap["ForwardingDemo"] = (BookChapter::MenuFunction) &(A7_Concepts::ForwardingDemo);
}

void A7_Concepts::ForwardingDemo()
{
    std::cout << "Making an aircraft carrier full of 747s" << std::endl;
    AircraftCarrier<Boeing747> aircraftCarrier747;
    aircraftCarrier747.Add(1e5);
    aircraftCarrier747.Add(1.2e5);
    std::cout << aircraftCarrier747.Print();

    std::cout << "Making an aircraft carrier full of gliders" << std::endl;
    AircraftCarrier<Glider> aircraftCarrier;
    aircraftCarrier.Add(10, "Romeo");
    aircraftCarrier.Add(10, "Juliet");
    std::cout << aircraftCarrier.Print();

}

void A7_Concepts::FoldDemo()
{
    std::cout << "Sum up a list of numbers in a template" << std::endl;
    auto v = sumPack(3, 4, 5.5, 2.0f, -4);    
    std::cout << "The sum of the numbers in the list is " << v << std::endl;

    std::cout << "Generic list constructor" << std::endl;
    auto newVector = generateVector<double, double>(2.0, 4, 5.5, -2);
    std::cout << "Generated the vector: " << std::endl;
    for (auto v : newVector)
    {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    std::cout << "Printing all arguments to a function" << std::endl;
    printFold("Hello!"s, ' ',"World ",2021);

}

void A7_Concepts::VariadicTemplateDemo()
{
    // Function overload deals with the zero arguments case
    std::cout << "Function overload to deal with zero case: does not print an endl." << std::endl;
    auto word = "World!";
    printVariadic("Hello"s, " ", word, 1);
    printVariadic("Hello"s, " ", word, 2);
    printVariadic("Hello"s, " ", word, '\n');

    std::cout << std::endl;
    std::cout << "Function not overloaded, constexpr if to deal with the zero case inserts a line break" << std::endl;
    printVariadicRecurse("Hello"s , ' ', word, "! ", 1);
    printVariadicRecurse("Hello"s , ' ', word, "! ", 2);
    printVariadicRecurse("Hello"s , ' ', word, "! ", 3);
}

A8_StandardLibrary::A8_StandardLibrary()
    :BookChapter("StandardLibrary")
{
    this->menuMap["StringDemo"] = (BookChapter::MenuFunction) &(A8_StandardLibrary::StringDemo);
    this->menuMap["ConsoleIODemo"] = (BookChapter::MenuFunction) &(A8_StandardLibrary::ConsoleIODemo);
}

std::string concatStringView(std::string_view a, std::string_view b)
{
    std::string res(a.length() + b.length(), '0');
    char* p = &res[0]; // Get the starting memory address of the combined array
    for (const char& c : a)
    {
        (*p++) = c;
    }
    std::copy(b.begin(), b.end(), p);
    return res;
}
void testRegexIterator(std::string input)
{
    std::cout << "Searching the string " << input << " for matches" << std::endl;
    std::regex pat {R"(\s+(\w+))"};
    for (std::sregex_iterator p(input.begin(), input.end(), pat); p!=std::sregex_iterator{}; ++p)
        std::cout << (*p)[1] << std::endl;
}

void A8_StandardLibrary::StringDemo()
{
    // Combining elements of a string
    std::cout << "Hello " << "World!" << std::endl;
    std::cout << "Hello "s + "World!" << std::endl;
    std::cout << "Hello "s + "World!"s << std::endl;
    std::cout << std::endl;

    // Substring and replace
    std::string phrase = "We don't serve food!";
    std::string subPhrase = phrase.substr(3, 5);
    for (auto & c: subPhrase) c = toupper(c); // Convert each char to uppercase
    phrase.replace(3, 5, subPhrase);
    std::cout << phrase << std::endl;
    std::cout << std::endl;

    //c-strings
    std::string s = "Shoulders of Giants";
    printf("Printf of string representation: %s\n", s.c_str());
    std::cout << "cout of string representation: " << s << std::endl;
    std::cout << "cout of c_str representation: " << s.c_str() << std::endl;
    std::cout << std::endl;

    // String view
    std::string s1 = "Hello ";
    const char* c1 = "Hello ";
    auto a1 = "Hello "s;
    std::string_view sv1 = "Hello "sv;
    std::string s2 = "World!";

    std::cout << concatStringView(s1, "World"s) << std::endl;
    std::cout << concatStringView(s1, "World"sv) << std::endl;
    std::cout << concatStringView(c1, "World") << std::endl;
    std::cout << concatStringView(c1, "World"sv) << std::endl;
    std::cout << concatStringView(s1, s2) << std::endl;
    std::cout << concatStringView(sv1, s2) << std::endl;
    // string views are {pointer, size} pairs
    std::cout << concatStringView({c1,6}, {&s2[0],5}) << std::endl;
    std::cout << concatStringView({&sv1.at(0),6}, {&s2[0],6}) << std::endl;
    std::cout << std::endl;

    // String view is read only, but this still allows:
    std::cout << "The third character in " << sv1 << " is " << sv1[2] << std::endl;
    // Out of range protection is provided by at()
    std::cout << "The third character in " << sv1 << " is " << sv1.at(2) << std::endl;
    std::cout << std::endl;

    // Regex match
    std::vector<std::string> postcodes = {"HP6 5PX", "SW1 1AA", "NN13 7BD", "AA1 1AA", "Hello World!", "Oops", "Pro1 4ot"};
    auto checker = PostcodeMatch();
    for (const auto s:postcodes)
    {
        std::cout << "The string " << s << (checker(s) ? " is " : " is not ") << "a valid postcode" << std::endl;
    }
    std::cout << std::endl;

    // Regex iterator
    std::string input1 = "aa as; asd ++e^asdf asdfg";
    std::string input2 = " cd ef2; ^^%12 g13 ww; ww";
    testRegexIterator(input1);
    testRegexIterator(input2);
}

void removeSpaceAndCapitalise(std::string& s)
{
    // Use the algorithm remove_if on the string to remove spaces
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char x) { return std::isspace(x); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), toupper);
}

void A8_StandardLibrary::ConsoleIODemo(void)
{
    // Read in a number and echo it back
    std::cout << "Input your favourite number" << std::endl;
    
    int favouriteNumber;
    std::cin >> favouriteNumber;
    std::cout << "Your favourite number is " << favouriteNumber << std::endl << std::endl;

    std::cout << "Input your two favourite numbers" << std::endl;
    int fav1, fav2;
    std::cin >> fav1 >> fav2;
    std::cout << "Your favourite numbers are " << fav1 << " and " << fav2 << std::endl << std::endl;

    std::cout << "Enter a full string with a space in the middle\n" << "Try \"a b\"" << std::endl;
    std::string str1, str2;
    std::cin >> str1;
    std::cout << "According to the read operator (>>), you entered: " << str1 << std::endl;
    std::cout << "Try again using getline, for example enter \"a b\"" << std::endl;
    std::getline(std::cin, str2);
    std::cout << "According to getline, you entered: " << str2 << std::endl;

    // This neat little block ensures that the file is closed after reading and all resources freed
    {
        std::ofstream os{"resources/temp.txt"};
        if (os)
        {
            std::cout << "I took the liberty of saving your responses so far out to a file:\n";
            os << favouriteNumber << std::endl;
            os << fav1 << " " << fav2 << std::endl;
            os << str1 << std::endl;
            os << str2 << std::endl;
        }
        else
        {
            std::cout << "You failed to open the file, sorry\n" << std::endl;
        }
    }

    // Now read them back in
    {
        std::ifstream is{"temp.txt"};
        std::vector<std::string> strings;
        for (std::string s1; getline(is, s1);)
        {
            strings.push_back(s1);
        }

        std::cout << "Here they are:" << std::endl;
        for (const auto& s2:strings)
        {
            std::cout << s2 << std::endl;
        }

        // Just for fun, lets run a little algorithm to remove the spaces and capitalise any characters
        std::for_each(strings.begin(), strings.end(), removeSpaceAndCapitalise);

        std::cout << std::endl;
        std::cout << "Here they are, but neatened up a bit:" << std::endl;
        for (const auto& s2:strings)
        {
            std::cout << s2 << std::endl;
        }

    }
}

Engine::Engine(double _torque, double _speed = 100)
{
    torque = _torque;
    speed = _speed;
}

double Engine::Power() const
{
    return torque * speed;
}

std::string Engine::Sound() const
{
    return "Vroom";
}

AfterburningEngine::AfterburningEngine(double _torque, double _speed = 100, double _afterburner = 1.0)
    : Engine{_torque, _speed}
{
    afterburner = _afterburner;
}

double AfterburningEngine::Power() const 
{
    return afterburner * Engine::Power();
}

std::string AfterburningEngine::Sound() const
{
    return "Bang";
}

RoadVehicle::RoadVehicle(int wheels, int doors, double accel)
{
    nWheels = wheels;
    nDoors = doors;
    acceleration = accel;
}

std::string RoadVehicle::Sound() const
{
    return "Brrrrrom";
}

double RoadVehicle::Speed() const
{
    // v = at
    return acceleration * 10;
}

F1Car::F1Car(int _wheels, double _accel)
    : RoadVehicle(_wheels, 0, _accel)
{

}

std::string F1Car::Sound() const
{
    return "Neow";
}

AirVehicle::AirVehicle(double dragForce, std::initializer_list<Engine*> _engines)
{
    drag = dragForce;
    engines = std::vector<Engine*>{};
    engines.insert(engines.begin(), _engines);
}

AirVehicle::AirVehicle(const AirVehicle& m)
    : AirVehicle(m.drag, {})
{
    for (auto e:m.engines)
    {
        auto newEngine = new Engine(*e);
        engines.push_back(newEngine);
    }
}

AirVehicle& AirVehicle::operator=(const AirVehicle& m)
{
    drag = m.drag;
    
    engines.clear();
    for (auto e:m.engines)
    {
        auto newEngine = new Engine(*e);
        engines.push_back(newEngine);
    }

    engines = m.engines;
    return *this; // Important for the equation syntax that a pointer to the current element is returned
}

double AirVehicle::Speed() const
{
    return Power() / drag;
}

double AirVehicle::Power() const
{
    double totalPower{0};
    for (auto e:engines)
    {
        totalPower += e->Power();
    }
    return totalPower;
}

std::string AirVehicle::Sound() const
{
    std::ostringstream ss;
    for (auto e:engines)
    {
        ss << e->Sound() << " ";
    }
    ss << '\0';
    return ss.str();
}

Boeing747::Boeing747(double dragForce)
    : AirVehicle(dragForce, {new Engine(1e6), new Engine(1e6), new Engine(1e6), new Engine(1e6)})
{
    
}

LockheedF35::LockheedF35(double dragForce)
    : AirVehicle(dragForce, {new AfterburningEngine(5e7,500, 1.2), new AfterburningEngine(5e7,500,1.2)})
{
    
}

std::string LockheedF35::Sound() const
{
    return "Bang";
}

Glider::Glider(double drag, std::string name)
    : AirVehicle(drag, {}), _name(name)
{

}

std::string Glider::Sound() const
{
    std::ostringstream s;
    s << "Hi! I'm a glider and my name is " << _name;
    return s.str();
}

Glider::Glider(const Glider& m)
    : AirVehicle(m), _name(m._name)
{
}

Glider& Glider::operator=(const Glider& m)
{
    AirVehicle::operator=(m);
    _name = m._name;
    return *this;
}

template<typename AirVehicle>
AircraftCarrier<AirVehicle>::AircraftCarrier() 
    : _aircraft(MyVector<AirVehicle>())
{
    
}

template<typename AirVehicle>
template<typename... VehicleArgs>
void AircraftCarrier<AirVehicle>::Add(VehicleArgs&&... v)
{
    _aircraft.append(AirVehicle(std::forward<VehicleArgs>(v)...));
}

template<typename AirVehicle>
std::string AircraftCarrier<AirVehicle>::Print()
{
    std::ostringstream os;
    os << "The aircraft carrier: " << '\n';
    for (int i = 0; i != _aircraft.size(); ++i)
    {
        os << _aircraft[i].Sound() << '\n';
    }
    return os.str();
}

template<typename T>
LessThan<T>::LessThan(const T& v) : comparator{v} {}
template<typename T>
constexpr bool LessThan<T>::operator()(const T& x) const {return x < comparator;}

BitChecker::BitChecker(const uint8_t p) : pos{p} {}
template<typename T>
constexpr bool BitChecker::operator()(const T& x) const {return x & (1 << (pos-1));}
// This works, but is undefined, unportable, and really messy
// constexpr bool BitChecker::operator()(T x) const {return (*reinterpret_cast<int*>(&x) & (1 << (pos-1)));}

PostcodeMatch::PostcodeMatch() {}
bool PostcodeMatch::operator()(std::string str) const {return std::regex_match(str, postcode);}