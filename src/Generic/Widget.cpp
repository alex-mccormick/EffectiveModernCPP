#include "Widget.h"

Widget::Widget(double x, double y) {
    _x = x;
    _y = y;
}

Widget::Widget() : Widget(0, 0){ }

int Widget::GetQuadrant() const {
    return 1 + ((_y < 0) << 1) + ((_x < 0)^(_y < 0));
}

double Widget::GetRadius() const {
    return pow(pow(_x, 2) + pow(_y, 2), 0.5);
}

bool Widget::IsPopulated() const {
    return !((_x==0) && (_y==0));
}

