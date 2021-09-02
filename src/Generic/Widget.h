#pragma once
 
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>

class Widget {
    public:
        constexpr Widget() : Widget(0, 0) { };
        constexpr Widget(double x, double y) : _x{x}, _y{y} { };
        Widget(const Widget& w);

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

            virtual void Draw() const;
            virtual double GetSpacing() &;
        
        protected:
            std::unique_ptr<Widget> _start;
            std::unique_ptr<Widget> _end;

            // TODO: make initialisers constexpr and enable compile time eval
    };

    class Circle : public Shape {
        public:
            Circle();

            virtual void Draw() const override;

        protected:
            std::unique_ptr<Widget> _centre;
    };

    class Face : public Circle {
        public:
            Face();
            Face(Widget*, Widget*);

            virtual void Draw() const final;

            std::vector<Widget>& GetEyes() &;
            std::vector<Widget>&& GetEyes() &&;

            virtual double GetSpacing() & override;
            double GetSpacing() && = delete;

        protected:
            std::vector<Widget> _eyes;
    };

}