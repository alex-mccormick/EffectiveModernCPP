#include "../include/stdafx.h"
#include "../Generic/BookChapter.h"
#include <string_view>
#include <regex>
#include "MyVector.h"
#include "MyVector.tpp"

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

struct SimpleVectorStruct {
    double* data;
    int sz;
};

class SimpleVector
{
    public:
        SimpleVector(int);
        ~SimpleVector();
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
        static void StructureDemo(void);
        static void ClassDemo(void);
        static void UnionDemo(void);
        static void VariantDemo(void);

};
class A3_Modularity
    : public BookChapter
{
    public:
        A3_Modularity();
        ~A3_Modularity();

    private:
        static void MatrixDemo(void);
};

class A4_Classes
    : public BookChapter
{
    public:
        A4_Classes();
        ~A4_Classes();

    private:
        static void AbstractClassDemo(void);
        static void UniquePtrDemo(void);
};

class A5_MoveAndCopy
    : public BookChapter
{
    public:
        A5_MoveAndCopy();
        ~A5_MoveAndCopy();

    private:
        static void SumMatrixDemo(void);
};

class A6_Templates
    : public BookChapter
{
    public:
        A6_Templates();

    private:
        static void IteratorDemo(void);
        static void MyVectorTemplateDemo(void);
        static void FunctionDemo(void);
        static void LambdaDemo(void);
        static void AliasDemo(void);
};

class A7_Concepts
    : public BookChapter
{
    public:
        A7_Concepts();

    private:
        static void VariadicTemplateDemo(void);
        static void FoldDemo(void);
        static void ForwardingDemo(void);
};

class A8_StandardLibrary
    : public BookChapter
{
    public:
        A8_StandardLibrary();

    private:
        static void StringDemo(void);
        static void ConsoleIODemo(void);
};

class Engine
{
    public:
        Engine(double, double);
        ~Engine() {};

        virtual double Power() const;
        virtual std::string Sound() const;

    private:
        double torque;
        double speed;
};

class AfterburningEngine
    : public Engine
{
    public:
        AfterburningEngine(double, double, double);

        double Power() const override;
        std::string Sound() const override;

    private:
        double afterburner;
};

class Vehicle
{
    public:
        virtual double Speed() const = 0;
        virtual std::string Sound() const = 0;
        virtual ~Vehicle() {}; // Destructor can be implemented here
};

class RoadVehicle
    : public Vehicle
{
    public:
        RoadVehicle(int, int, double);

        std::string Sound() const override;
        double Speed() const override;

    private:
        int nWheels;
        int nDoors;
        double acceleration;
};

class F1Car
    : public RoadVehicle
{
    public:
        F1Car(int, double);
        std::string Sound() const override;
};
class AirVehicle
    : public Vehicle
{
    public:
        AirVehicle(double, std::initializer_list<Engine*>);
        AirVehicle() {};

        AirVehicle(const AirVehicle&); // Copy constructor
        AirVehicle& operator=(const AirVehicle&); // Copy assignment

        std::string Sound() const override;
        double Speed() const override;
        double Power() const;

    private:
        double drag;
        std::vector<Engine*> engines;
};

class Boeing747
    : public AirVehicle
{
    public:
        Boeing747(double);
        Boeing747() : AirVehicle() {};
};

class LockheedF35
    : public AirVehicle
{
    public:
        LockheedF35(double);
        LockheedF35() : AirVehicle() {};

        std::string Sound() const override;
};

class Glider
    : public AirVehicle
{
    public:
        Glider(double, std::string);
        Glider() : AirVehicle() {_name="Default"; };
        Glider(const Glider&); // Copy constructor
        Glider& operator=(const Glider&); // Copy assignment

        std::string Sound() const override;

    private:
        std::string _name;
};

template<typename AirVehicle>
class AircraftCarrier
{
    public:
        AircraftCarrier();

        template<typename... VehicleArgs>
        void Add(VehicleArgs&&...);
        std::string Print();

    private:
        MyVector<AirVehicle> _aircraft;
};


template<typename T>
class LessThan {
    private:
        const T comparator;

    public:
        LessThan(const T&);
        constexpr bool operator()(const T&) const;
};

class BitChecker {
    private:
        const uint8_t pos;
    public:
        BitChecker(const uint8_t);
        template<typename T>
        constexpr bool operator()(const T&) const;
        // constexpr bool operator()(T) const;
};

class PostcodeMatch {
    private:
        const std::regex postcode{R"(^[A-Z]{1,2}\d[A-Z\d]? ?\d[A-Z]{2}$)"};
    public:
        PostcodeMatch();
        bool operator()(std::string) const;
};
