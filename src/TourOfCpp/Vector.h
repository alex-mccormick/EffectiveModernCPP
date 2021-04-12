#include <iostream>
#include <memory>
#include <initializer_list>

template<typename T>
class Vector {

    public:
        using value_type = T;

        Vector();
        ~Vector();
        Vector(const Vector&); // Copy constructor
        Vector(Vector&&); // Move constructor
        Vector& operator=(const Vector&); // Copy assignment
        Vector& operator=(Vector&&); // Move assignment

        explicit Vector(int);
        explicit Vector(T);
        Vector(int, T);
        Vector(std::initializer_list<T>);

        template<typename Iterator>
        Vector(Iterator, Iterator) -> Vector<typename Iterator::value_type>;

        T sum();
        T& operator[](int);
        friend T* begin(Vector& v);
        friend T* end(Vector& v);

        int size() const;
        bool isEmpty() const;

        friend void print(std::ostream&, const Vector&);
        friend std::ostream& operator<<(std::ostream& os, const Vector&);

    private:
        std::unique_ptr<T[]> data;
        int sz;

};