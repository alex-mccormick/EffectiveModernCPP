#include "TourOfCpp.h"
#include "Matrix.h"
#include "MyVector.h"
#include "MyVector.tpp"
#include "SimpleCollection.h"
#include <variant>
#include <sstream>
#include <memory>
#include <ctime>
#include <chrono>
#include <string>

using namespace std::string_literals; // enables s-suffix for std::string literals

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
    engines = std::vector<Engine*>{_engines};
}
AirVehicle::~AirVehicle()
{
    auto i{0};
    for (auto e:engines)
    {
        ++i;
        delete e;
    }
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


template<typename T>
LessThan<T>::LessThan(const T& v) : comparator{v} {}
template<typename T>
constexpr bool LessThan<T>::operator()(const T& x) const {return x < comparator;}

BitChecker::BitChecker(const uint8_t p) : pos{p} {}
template<typename T>
constexpr bool BitChecker::operator()(const T& x) const {return x & (1 << (pos-1));}
// This works, but is undefined, unportable, and really messy
// constexpr bool BitChecker::operator()(T x) const {return (*reinterpret_cast<int*>(&x) & (1 << (pos-1)));}