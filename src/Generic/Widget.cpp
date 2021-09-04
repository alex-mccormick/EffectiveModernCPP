#include "Widget.h"

Widget::Widget(Widget&& w) : _x{w._x}, _y{w._y} { std::cout << "Move constructing a widget\n"; };

std::ostream& operator<<(std::ostream& os, const Widget& widget)
{
    os << "(" << widget.get_x() << ", " << widget.get_y() << ")";
    return os;
}

double Widget::GetRadius() const {
    return std::pow(std::pow(_x, 2) + std::pow(_y, 2), 0.5);
}

bool Widget::IsPopulated() const {
    return !((_x==0) && (_y==0));
}

namespace Overriding {

    Shape::Shape() {
        _start = std::make_unique<Widget>(-1, -1);
        _end = std::make_unique<Widget>(1, 2);
    }

    void Shape::Draw() const {
        std::cout << "Drawing a shape" << std::endl;
        std::cout << "Start: " << *_start << std::endl;
        std::cout << "End: " << *_end << std::endl;
    }
    
    double Shape::GetSpacing() & {
        std::cout << "Getting shape spacing\n";
        return std::hypot(_start->get_x() - _end->get_x(), _start->get_y() - _end->get_y());
    }

    Circle::Circle() : Shape() {
        auto x = (_start->get_x() + _end->get_x()) / 2;
        auto y = (_start->get_y() + _end->get_y()) / 2;

        _centre = std::make_unique<Widget>(x, y);
    }

    void Circle::Draw() const {
        std::cout << "Drawing a circle" << std::endl;
        std::cout << "Centre: " << *_centre << std::endl;
    }

    Face::Face() : Circle() {
        _eyes.push_back(Widget(-0.1, 0.4));
        _eyes.push_back(Widget( 0.1, 0.4));
    }

    Face::Face(Widget* w1, Widget* w2) {
        _eyes.push_back(*w1);
        _eyes.push_back(*w2);
    }

    void Face::Draw() const {
        Circle::Draw();
        std::cout << "Drawing a face" << std::endl;
        int nEyes = 0;
        for (const auto& e : _eyes) {
            std::cout << "Eye " << ++nEyes << ": " << e << std::endl;
        }
    }

    // Called on lvalue reference members (i.e. normal class members)
    std::vector<Widget>& Face::GetEyes() & {
        std::cout << "Copied value out of lvalue reference function\n";
        return _eyes;
    }
    // Called on rvalue reference members (i.e. make_widget().GetEyes())
    std::vector<Widget>&& Face::GetEyes() && {
        std::cout << "Moved value out of rvalue reference function\n";
        return std::move(_eyes);
    }

    // Called on lvalue referece members (i.e. normal class members)
    double Face::GetSpacing() & {
        std::cout << "Getting eye spacing of lvalue ref member\n";
        return std::hypot(_eyes[0].get_x() - _eyes[1].get_x(), _eyes[0].get_y() - _eyes[1].get_y());
    }
}