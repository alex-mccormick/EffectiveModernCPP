#include "Matrix.h"
#include <math.h>

Matrix::Matrix(int s)
    :data{new double[s*s]}, sz{s}
{
    if (s <= 0)
    {
        throw std::out_of_range{"Matrix cannot be empty"};
    }
}
Matrix::Matrix(int s, double value)
    : Matrix{s}
{
    for (auto i = 0; i != s*s; ++i)
    {
        data[i] = value;
    }
}
int Matrix::size() const
{
    return sz;
}

double& Matrix::operator[](int i)
{
    if (i <= 0 || i >= pow(size(), 2))
        throw std::out_of_range{"Matrix::operator[] out of range"};
    return data[i];
}
double Matrix::idx(int i, int j) const
{
    if (i < 0 || i >= this->size() || j < 0 || j >= this->size())
        throw std::out_of_range{"Matrix::operator[] out of range"};
    return data[i * sz + j];
}

Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    if (m1.size() == m2.size())
    {
        const int size {m1.size()};
        Matrix* sum = new Matrix{size};
        for (auto i = 0; i != size*size; ++i)
        {
            sum->data[i] = m1.data[i] + m2.data[i];
        }
        return *sum;
    }
    else
    {
        throw std::out_of_range{"Matrices must be the same size"};
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix &m)
{
    for (auto i = 0; i != m.size(); ++i)
    {
        for (auto j = 0; j != m.size()-1; ++j)
        {
            os << m.idx(i, j) << ",\t";
        }
        os << m.idx(i, m.size()-1);
        os << std::endl;
    }
    return os;
}

void Matrix::print(std::ostream& os, const Matrix &m)
{
    os << m << std::endl;
}