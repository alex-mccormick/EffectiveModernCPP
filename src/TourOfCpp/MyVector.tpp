#pragma once
#include "MyVector.h"
#include <iterator>

template<typename T>
MyVector<T>::MyVector()
    : sz{0}, data{std::unique_ptr<T[]>()}
{
}

template<typename T>
MyVector<T>::~MyVector()
{
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& v)
    : MyVector(v.size())
{
    // Copy constructor, so we need to copy the data
    for (auto i = 0; i != sz; ++i)
    {
        data[i] = v.data[i];
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& v)
    : data{std::move(v.data)}, sz{v.sz}
{
    v.data = std::unique_ptr<T[]>();
    v.sz = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& v)
{
    // Copy assignment
    auto newData = std::make_unique<T[]>(v.sz);
    for (auto i = 0; i != sz; ++i)
    {
        newData[i] = v.data[i];
    }
    std::swap(data, newData);

    sz = v.sz;
    return *this; // Important for the equation syntax that a pointer to the current element is returned
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& v)
{
    // Move assignment
    this->sz = v.sz;
    this->data = std::move(v.data);
    v.data = std::make_unique<T[]>();
    v.sz = 0;
    return *this;
}

template<typename T>
MyVector<T>::MyVector(int s)
    :sz{s}
{
    if (s <= 0)
        throw std::out_of_range{"MyVector cannot be empty"};

    data = std::make_unique<T[]>(s);
}

template<typename T>
MyVector<T>::MyVector(int s, T value)
    : MyVector(s)
{        
    for (auto i = 0; i != s; ++i)
    {
        data[i] = value;
    }
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> init)
    : MyVector(init.size())
{
    int i{0};
    for (const auto& x:init)
    {
        data[i++] = x;
    }
}

template<typename T>
template<typename Iter>
MyVector<T>::MyVector(Iter s, Iter e)
{
    int i{0};
    for (auto x = s; x != e; ++x)
    {
        ++i;
    }
    sz = i;
    data = std::make_unique<T[]>(i);

    i=0;
    for (auto x = s; x != e; ++x)
    {
        data[i] = x.get();
        ++i;
    }
}

template<typename T>
int MyVector<T>::size() const
{
    return sz;
}
template<typename T>
bool MyVector<T>::isEmpty() const
{
    return (sz == 0);
}

template<typename T>
T& MyVector<T>::operator[](int i)
{
    if (i < 0 || i >= sz)
        throw std::out_of_range{"MyVector<T>::operator[] out of range"};
    return data.get()[i];
}

template<typename T>
T MyVector<T>::sum()
{
    T runningTotal{0};
    for (const auto& x : *this)
    {
        runningTotal += x;
    }
    return runningTotal;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
    return MyVector<T>::Iterator(sz ? data.get() : nullptr);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
    return MyVector<T>::Iterator(sz ? data.get() + sz : nullptr);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, MyVector<T> &v)
{
    for (const auto ve:v)
    {
        os << ve << std::endl;
    }
    return os;
}

template<typename T>
void print(std::ostream& os, MyVector<T> &v)
{
    os << v << std::endl;
}