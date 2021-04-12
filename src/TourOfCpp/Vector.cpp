#include "Vector.h"

template<typename T>
Vector<T>::Vector()
    : Vector(1)
{
    data[0] = 0;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v)
    : Vector<T>(v.size())
{
    // Copy constructor, so we need to copy the data
    for (auto i = 0; i != sz; ++i)
    {
        data[i] = v.data[i];
    }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& v)
    : data{std::move(v.data)}, sz{v.sz}
{
    v.data = std::unique_ptr<T[]>();
    v.sz = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    // Copy assignment
    auto newData = std::make_unique<T[]>(new T[v.sz]);
    for (auto i = 0; i != sz; ++i)
    {
        newData[i] = v.data[i];
    }
    std::swap(data, newData);

    sz = v.sz;
    return *this; // Important for the equation syntax that a pointer to the current element is returned
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v)
{
    // Move assignment
    this->sz = v.sz;
    this->data = std::move(v.data);
    v.data = std::make_unique<T[]>();
    v.sz = 0;
    return *this;
}

template<typename T>
Vector<T>::Vector(int s)
    :data{std::make_unique<T[]>(new T[s])}, sz{s}
{
    if (s < 0)
    {
        throw std::out_of_range{"Vector cannot be empty"};
    }
}

template<typename T>
// If the matrix is initialised with a double, the explicit constructor forces this
// to be used as the sole value in the matrix with a size of 1.
Vector<T>::Vector(T d)
    :Vector<T>(1, d)
{ }

template<typename T>
Vector<T>::Vector(int s, T value)
    : Vector<T>{s}
{
    for (auto i = 0; i != s; ++i)
    {
        data[i] = value;
    }
}

//TODO: Initialiser list constructor


template<typename T>
int Vector<T>::size() const
{
    return sz;
}
template<typename T>
bool Vector<T>::isEmpty() const
{
    return (sz == 0);
}

template<typename T>
T& Vector<T>::operator[](int i)
{
    if (i < 0 || i >= this->size())
        throw std::out_of_range{"Vector<T>::operator[] out of range"};
    return data.get()+i;
}

template<typename T>
T Vector<T>::sum()
{
    T runningTotal{0};
    for (auto& x : *this)
    {
        runningTotal += x;
    }
    return runningTotal;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T> &v)
{
    for (auto i = 0; i != v.size(); ++i)
    {
        os << v[i] << std::endl;
    }
    return os;
}

template<typename T>
T* begin(Vector<T>& v)
{
    return (v.size() ? &v[0] : nullptr);
}

template<typename T>
T* end(Vector<T>& v)
{
    int sz = v.size();
    return (sz ? &v[0] + sz : nullptr);
}

template<typename T>
void print(std::ostream& os, const Vector<T> &v)
{
    os << v << std::endl;
}