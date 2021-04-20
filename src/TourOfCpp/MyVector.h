#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

template<typename T>
class MyVector {

    public:

        struct Iterator 
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;  // or also value_type*
            using reference         = T&;  // or also value_type&

            Iterator(pointer ptr) : m_ptr(ptr) {}
            reference get() const {return *m_ptr;};
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }

            // Prefix increment
            Iterator& operator++() { m_ptr++; return *this; }  
            Iterator operator+(int a) { m_ptr+=a; return *this; }  

            // Postfix increment
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };    

            private:

                pointer m_ptr;
        };

        using value_type = T;

        MyVector();
        ~MyVector();
        MyVector(const MyVector<T>&); // Copy constructor
        MyVector(MyVector<T>&&); // Move constructor
        MyVector<T>& operator=(const MyVector<T>&); // Copy assignment
        MyVector<T>& operator=(MyVector<T>&&); // Move assignment

        explicit MyVector(int);
        MyVector(int, T);
        MyVector(std::initializer_list<T>);

        template<typename Iter>
        MyVector(Iter s, Iter e);
        T sum();
        T& operator[](int);

        int size() const;
        bool isEmpty() const;

        Iterator begin();
        Iterator end();

    private:
        std::unique_ptr<T[]> data;
        int sz;

};