#include <iostream>

class Matrix {
    public:
        Matrix(int);
        Matrix(int, double);
        double idx(int, int) const;
        double& operator[](int);
        friend Matrix operator+(const Matrix&, const Matrix&);
        int size() const;

        void print(std::ostream&, const Matrix&);
        friend std::ostream& operator<<(std::ostream& os, const Matrix&);

    private:
        double* data;
        int sz;
};
