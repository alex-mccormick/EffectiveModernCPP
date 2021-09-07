#pragma once
 
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>

class Widget {
    public:
        constexpr Widget() : Widget(0, 0) { };
        constexpr Widget(double x, double y) : _x{x}, _y{y} { };
        
        Widget(Widget&& w); // The move constructor is defined
        // Since the move constructor is defined, the copy constructor will be deleted
        Widget(const Widget& w) = default; // Explicitly define the default copy constructor

        // Destructor will be default, allows constexpr Widget

        constexpr int GetQuadrant() const {
            return 1 + ((_y < 0) << 1) + ((_x < 0)^(_y < 0));
        };

        double GetRadius() const;
        bool IsPopulated() const;

        constexpr double get_x() const {return _x;};
        constexpr double get_y() const {return _y;};
        
    private:
        double _x{0};
        double _y{0};

};

namespace Overriding {

    class Shape {
        public:
            Shape();
            virtual ~Shape() {};

            virtual void Draw() const;
            virtual double GetSpacing() &;
        
        protected:
            std::unique_ptr<Widget> _start;
            std::unique_ptr<Widget> _end;
    };

    class Circle : public Shape {
        public:
            Circle();
            virtual ~Circle() override {};

            virtual void Draw() const override;

        protected:
            std::unique_ptr<Widget> _centre;
    };

    class Face : public Circle {
        public:
            Face();
            Face(Widget*, Widget*);
            virtual ~Face() override {};

            virtual void Draw() const final;

            std::vector<Widget>& GetEyes() &;
            std::vector<Widget>&& GetEyes() &&;

            virtual double GetSpacing() & override;
            double GetSpacing() && = delete;

        protected:
            std::vector<Widget> _eyes;
    };


};

enum class ShapeType {Shape, Circle, Face};

template<typename... Ts>
auto shape_factory(const ShapeType type, Ts&&... params)
{
    std::unique_ptr<Overriding::Shape> ptr{nullptr};

    if (type == ShapeType::Circle)
    {
        ptr.reset(new Overriding::Circle(std::forward<Ts>(params)));
    }
    else if (type == ShapeType::Face)
    {
        ptr.reset(new Overriding::Face(std::forward<Ts>(params)));
    }
    else
    {
        ptr.reset(new Overriding::Shape(std::forward<Ts>(params)));
    }

    return ptr;
};

std::string shape_name(const ShapeType type) {
    switch (type) {
        case ShapeType::Shape:
            return "Shape";
        case ShapeType::Circle:
            return "Circle";
        case ShapeType::Face:
            return "Face";
        default: 
            return "";
    }
};

template<typename... Ts>
auto shape_factory_with_deleter(const ShapeType type, Ts&&... params)
{
    auto shapeString = shape_name(type);

    auto delShape = [=] (Overriding::Shape* shape) {
        if (shape)
            std::cout << "Deleting " << shapeString << "\n";
        delete shape;
    };

    std::unique_ptr<Overriding::Shape,decltype(delShape)> ptr{nullptr, delShape};
    
    if (type == ShapeType::Circle)
    {
            ptr.reset(new Overriding::Circle(std::forward<Ts>(params)));
    }
    else if (type == ShapeType::Face)
    {
        ptr.reset(new Overriding::Face(std::forward<Ts>(params)));
    }
    else
    {
        ptr.reset(new Overriding::Shape(std::forward<Ts>(params)));
    }

    return ptr;
};