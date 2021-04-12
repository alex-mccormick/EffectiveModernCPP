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
        ~AirVehicle();

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
};

class LockheedF35
    : public AirVehicle
{
    public:
        LockheedF35(double);

        std::string Sound() const override;
};
