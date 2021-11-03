#pragma once
 
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>
#include <atomic>

class Widget {
    public:
        constexpr Widget() : Widget(0, 0) { };
        constexpr Widget(double x, double y) : _x{x}, _y{y} { };
        
        Widget(Widget&& w); // The move constructor is defined
        Widget& operator=(Widget&& w) = default;
        // Since the move constructor is defined, the copy constructor will be deleted

        Widget(const Widget& w) = default; // Explicitly define the default copy constructor
        Widget& operator=(const Widget&) = default; // Same for the copy assignment

        // Destructor will be default, allows constexpr Widget

        constexpr int GetQuadrant() const {
            return 1 + ((_y < 0) << 1) + ((_x < 0)^(_y < 0));
        };

        double GetRadius() const;
        double GetDistanceTo(const Widget& rhs) const;
        bool IsPopulated() const;

        constexpr double get_x() const {return _x;};
        constexpr double get_y() const {return _y;};
        
    protected:
        double _x{0};
        double _y{0};

};

std::ostream& operator<<(std::ostream&, const Widget&);

class ExWidget : public Widget, public std::enable_shared_from_this<ExWidget> {

    public:
        ExWidget() : ExWidget(0, 0) { };
        ExWidget(double x, double y) : Widget(x, y) { };

        double& get_x() {return _x;};
        double& get_y() {return _y;};

        void ProcessWidget(double scalar, std::vector<std::shared_ptr<ExWidget>>& processedWidgets);
        void ProcessWidgetWithThis(double scalar, std::vector<std::shared_ptr<ExWidget>>& processedWidgets);

};

namespace Overriding {

    class Shape {
        public:
            Shape();
            virtual ~Shape() { ShapesLeft--; };


            virtual void Draw() const;
            virtual double GetSpacing() &;

            static std::atomic<int> ShapesLeft;
        
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
            Face(const Widget&, const Widget&);
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

inline std::string shape_name(const ShapeType type) {
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
auto shape_factory(const ShapeType type, Ts&&... params)
{
    std::unique_ptr<Overriding::Shape> ptr{nullptr};

    if (type == ShapeType::Circle)
    {
        ptr.reset(new Overriding::Circle(std::forward<Ts>(params)...));
    }
    else if (type == ShapeType::Face)
    {
        ptr.reset(new Overriding::Face(std::forward<Ts>(params)...));
    }
    else
    {
        ptr.reset(new Overriding::Shape(std::forward<Ts>(params)...));
    }

    return ptr;
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
    
    if (type == ShapeType::Face)
    {
        ptr.reset(new Overriding::Face(std::forward<Ts>(params)...));
    }

    return ptr;
};

template<typename... Ts>
auto shape_factory_with_returning_deleter(const ShapeType type, Ts&&... params)
{
    auto shapeString = shape_name(type);

    auto delShape = [=] (Overriding::Shape* shape) {
        if (shape)
            std::cout << "Deleting " << shapeString << " using a returning deleter\n";
        delete shape;
        return Overriding::Shape::ShapesLeft > 0;
    };

    std::unique_ptr<Overriding::Shape,decltype(delShape)> ptr{nullptr, delShape};
    
    if (type == ShapeType::Face)
    {
        ptr.reset(new Overriding::Face(std::forward<Ts>(params)...));
    }

    return ptr;
};