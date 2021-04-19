#pragma once

SimpleCollection::SimpleCollection(double a, double b)
{
    this->value_a = a;
    this->value_b = b;
}

SimpleCollection::~SimpleCollection()
{

}

double SimpleCollection::GetA()
{
    return this->value_a;
}
double SimpleCollection::GetB()
{
    return this->value_b;
}

template<typename T>
SimpleTemplateCollection<T>::SimpleTemplateCollection(T a, T b)
{
    this->value_a = a;
    this->value_b = b;
}

template<typename T>
SimpleTemplateCollection<T>::~SimpleTemplateCollection()
{

}

template<typename T>
T SimpleTemplateCollection<T>::GetA()
{
    return this->value_a;
}

template<typename T>
T SimpleTemplateCollection<T>::GetB()
{
    return this->value_b;
}