#include <iostream>

class Matrix {
    public:

        // Defaults
        Matrix(); // Default constructor
        ~Matrix(); // Destructor
        Matrix(const Matrix&); // Copy constructor
        Matrix(Matrix&&); // Move constructor
        Matrix& operator=(const Matrix&); // Copy assignment
        Matrix& operator=(Matrix&&); // Move assignment

        explicit Matrix(int);
        explicit Matrix(double);
        Matrix(int, double);
        double idx(int, int) const;
        double sum();
        double& operator[](int);
        friend Matrix operator+(const Matrix&, const Matrix&);
        friend double* begin(Matrix& v);
        friend double* end(Matrix& v);

        int size() const;
        bool isEmpty() const;

        void print(std::ostream&, const Matrix&);
        friend std::ostream& operator<<(std::ostream& os, const Matrix&);

    private:
        double* data;
        int sz;
};
