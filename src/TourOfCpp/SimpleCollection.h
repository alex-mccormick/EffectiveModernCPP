#pragma once
class SimpleCollection {

    public:
        SimpleCollection(double, double);
        ~SimpleCollection();

        double GetA();
        double GetB();

    private:
        double value_a;
        double value_b;
};

template<typename T>
class SimpleTemplateCollection {

    public:
        SimpleTemplateCollection(T, T);
        ~SimpleTemplateCollection();

        T GetA();
        T GetB();

    private:
        T value_a;
        T value_b;
};

#include "SimpleCollection.tpp"