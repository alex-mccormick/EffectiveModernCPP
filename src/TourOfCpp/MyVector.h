#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <cstddef>  // For std::ptrdiff_t
#include <utility>
#include <exception>

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
        struct Const_Iterator 
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = const T*;  // or also value_type*
            using reference         = const T&;  // or also value_type&

            Const_Iterator(pointer ptr) : m_ptr(ptr) {}
            reference get() const {return *m_ptr;};
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }

            // Prefix increment
            Const_Iterator& operator++() { m_ptr++; return *this; }  
            Const_Iterator operator+(int a) { m_ptr+=a; return *this; }  

            // Postfix increment
            Const_Iterator operator++(int) { Const_Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Const_Iterator& a, const Const_Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Const_Iterator& a, const Const_Iterator& b) { return a.m_ptr != b.m_ptr; };    

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
        MyVector(Iter, Iter);
        T sum();
        T& operator[](int);

        void append(T);

        int size() const;
        bool isEmpty() const;

        Iterator begin();
        Iterator end();
        Const_Iterator begin() const;
        Const_Iterator end() const;

    private:
        std::unique_ptr<T[]> data;
        int sz;

};

template<typename TKey, typename TVal>
class MyMap {

    public:

        using map_type = MyMap<TKey, TVal>;
        using key_type = TKey;
        using mapped_type = TVal;
        using value_type = std::pair<key_type, mapped_type>;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using map_reference = mapped_type&;
        using reference = value_type&;
        using const_reference = const value_type&;

        
        struct iterator {

            iterator(TKey* it, map_type* mapRef) : ptr{it}, map{mapRef}
            {
                v = value_type();
            };

            void refreshPair() { v = (ptr ? std::make_pair(*ptr, map->get(*ptr)) : value_type()); }
            value_type get() const { refreshPair(); return v;}
            value_type operator*() { refreshPair(); return v; }
            pointer operator->() { refreshPair(); return &v; }

            // Prefix increment
            iterator& operator++() { ptr++; return *this; }  
            iterator operator+(int a) { ptr+=a; return *this; }  

            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const iterator& a, const iterator& b) { return a.ptr == b.ptr; };
            friend bool operator!= (const iterator& a, const iterator& b) { return a.ptr != b.ptr; };    

            private:
                value_type v;
                TKey* ptr;
                map_type * map;
        };

        MyMap();
        MyMap(const MyVector<TKey>&, const MyVector<TVal>&);
        MyMap(MyVector<TKey>&&, MyVector<TVal>&&);
        MyMap(std::initializer_list<value_type>);

        // TODO: copy and move constructors, mirroring vector implementation

        map_type& Add(value_type);
        map_type& Add(pointer);
        map_type& Add(reference);
        map_type& Add(const_reference);
        map_type& Add(key_type, pointer);
        map_type& Add(key_type, mapped_type);

        map_reference operator[](key_type);

        map_reference get(key_type);
        map_reference get(key_type) const;

        bool isKey(key_type) const;
        
        iterator begin();
        // const_iterator begin();
        iterator end();
        // const_iterator end();
        
        std::size_t size() const;
        
    private:
        MyVector<key_type> _keys;
        MyVector<mapped_type> _vals;
        int sz;
};