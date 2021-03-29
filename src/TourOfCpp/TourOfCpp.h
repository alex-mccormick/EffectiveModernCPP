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
class A3_Modularity
    : public BookChapter
{
    public:
        A3_Modularity();
        ~A3_Modularity();

    private:
        void MatrixDemo(void);
};

class A4_Classes
    : public BookChapter
{
    public:
        A4_Classes();
        ~A4_Classes();

    private:
        void AbstractClassDemo(void);
        void UniquePtrDemo(void);
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
