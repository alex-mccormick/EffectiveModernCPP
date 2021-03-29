#include "TourOfCpp.h"
#include <variant>
#include <sstream>
#include "Matrix.h"

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

void A4_Classes::UniquePtrDemo()
{
    // TODO: unique ptr demo
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
    for (auto e:engines)
    {
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