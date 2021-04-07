#include "Matrix.h"
#include <math.h>

// Default functions

Matrix::Matrix()
 : Matrix(1)
{
    data[0] = 0;
}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix::Matrix(const Matrix& m)
    : Matrix(m.size())
{
    // Copy constructor, so we need to copy the data
    for (auto i = 0; i != sz*sz; ++i)
    {
        data[i] = m.data[i];
    }
}

Matrix::Matrix(Matrix&& m)
    : data{m.data}, sz{m.sz}
{
    // Move constructor, so we can just transfer the pointer
    // Definitely don't call the old destructor as that will free the memory

    // However, we must not leave a dangling reference
    m.data = nullptr;
    m.sz = 0;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    // Copy assignment
    double* newData = new double[m.sz*m.sz];
    sz = m.sz;

    for (auto i = 0; i != sz*sz; ++i)
    {
        newData[i] = m.data[i];
    }
    // We are copying m's values into the current (already intialised) matrix
    // So it is safe to release the values held at the current pointer
    delete[] data;
    // move over the pointer to the newly created array
    data = newData;
    return *this; // Important for the equation syntax that a pointer to the current element is returned
}

Matrix& Matrix::operator=(Matrix&& m)
{
    // Move assignment
    this->sz = m.sz;
    this->data = m.data;
    m.data = nullptr;
    m.sz = 0;
    return *this;
}


// If matrix is initialised with an int, the explicit constructor forces this
// to be used as the size of the matrix, and the remainder initiliases to empty
Matrix::Matrix(int s)
    :data{new double[s*s]}, sz{s}
{
    if (s <= 0)
    {
        throw std::out_of_range{"Matrix cannot be empty"};
    }
}
// If the matrix is initialised with a double, the explicit constructor forces this
// to be used as the sole value in the matrix with a size of 1.
Matrix::Matrix(double d)
    :Matrix(1, d)
{ }

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
bool Matrix::isEmpty() const
{
    return (sz == 0);
}

double& Matrix::operator[](int i)
{
    if (i < 0 || i >= pow(this->size(), 2))
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
        // One implementation of this is to use pointers throughout
        // const int size {m1.size()};
        // Matrix* sum = new Matrix{size};
        // for (auto i = 0; i != size*size; ++i)
        // {
        //     sum[i] = m1[i] + m2[i];
        // }
        // return *sum;

        // But there is a neater implementation when we have move constructors defined
        // The value is returned using a move constructor
        const int size {m1.size()};
        Matrix sum{size};
        for (auto i = 0; i != size*size; ++i)
        {
            sum[i] = m1.data[i] + m2.data[i];
        }
        return sum;

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