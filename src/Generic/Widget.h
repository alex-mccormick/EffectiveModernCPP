#include <math.h>

class Widget {
    public:
        Widget();
        Widget(double x, double y);

        int GetQuadrant() const;
        double GetRadius() const;
        bool IsPopulated() const;
        
    private:
        double _x{0};
        double _y{0};

};