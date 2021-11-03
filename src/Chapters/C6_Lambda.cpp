#include "Chapters.h"
#include "../Generic/Widget.h"
#include <sstream>
#include <functional>
#include <vector>
#include <memory>

int C6_Lambda::staticDivisor = 9;

C6_Lambda::C6_Lambda()
    : BookChapter("Lambda") {
    this->menuMap["CaptureModes"] = (BookChapter::MenuFunction) &(C6_Lambda::CaptureModes);
    this->menuMap["InitCapture"] = (BookChapter::MenuFunction) &(C6_Lambda::InitCapture);
    this->menuMap["Bind"] = (BookChapter::MenuFunction) &(C6_Lambda::Bind);
    this->menuMap["GenericLambda"] = (BookChapter::MenuFunction) &(C6_Lambda::GenericLambda);
}

template<typename T>
void EvaluateFilters(const std::vector<T>& range, const std::vector<std::function<bool(T)>>& filters)
{
    for (const auto& f:filters)
    {    
        bool somethingMeetsTheFilter{false};
        std::ostringstream numbersMeetingFilter;
        for (T i:range)
        {
            if (!f(i))
            {
                somethingMeetsTheFilter = true;
                numbersMeetingFilter << i << ", ";
            }
        }
        if (somethingMeetsTheFilter)
        {
            std::cout << "The following numbers meet the filter: " << numbersMeetingFilter.str() << std::endl;
        }
        else
        {
            std::cout << "Nothing met the filter" << std::endl;
        }
    }
}


void C6_Lambda::CaptureModes()
{
    std::vector<std::function<bool(int)>> filters;
    std::vector<int> numbers(30,0);
    for (int i = 0; i != 30; ++i)
    {
        numbers[i] = i;
    }

    int defaultDivisor{11};
    int byValDivisor{3};
    int byRefDivisor{5};
    staticDivisor = 9;

    auto defaultCapture = [](int value){return value % 11;};
    auto byValCapture = [=](int value){return value % byValDivisor;};
    auto byRefCapture = [&](int value){return value % byRefDivisor;};
    auto staticCapture = [](int value){return value % staticDivisor;};

    filters.push_back(defaultCapture);
    filters.push_back(byValCapture);
    filters.push_back(byRefCapture);
    filters.push_back(staticCapture);

    EvaluateFilters(numbers, filters);

    // Make some changes, see if things stay the same
    defaultDivisor = 12;
    byValDivisor = 4;
    byRefDivisor = 6;
    staticDivisor = 10;

    EvaluateFilters(numbers, filters);
}

void C6_Lambda::InitCapture()
{
    
    std::vector<std::function<bool(int)>> filters;
    std::vector<std::function<bool(int)>> reffilters;

    std::vector<int> numbers(30,0);
    for (int i = 0; i != 30; ++i)
    {
        numbers[i] = i;
    }

    int defaultDivisor{11};
    int byValDivisor{3};
    int byRefDivisor{5};
    staticDivisor = 9;

    auto defaultCapture = [div = 11](int value){return value % div;};
    auto byValCapture = [div = byValDivisor](int value){return value % div;};
    auto staticCapture = [div = staticDivisor](int value){return value % div;};

    filters.push_back(defaultCapture);
    filters.push_back(byValCapture);
    filters.push_back(staticCapture);
    
    auto byRefCapture = [div = &byRefDivisor](int value){return value % *div;};

    reffilters.push_back(byRefCapture);

    EvaluateFilters(numbers, filters);
    EvaluateFilters(numbers, reffilters);

    // Make some changes, see if things stay the same
    defaultDivisor = 12;
    byValDivisor = 4;
    byRefDivisor = 6;
    staticDivisor = 10;

    EvaluateFilters(numbers, filters);
    EvaluateFilters(numbers, reffilters);

    // Now do something with a more complicated list of filters

    Widget w1(1, 1);
    Widget w2(3, 4);

    std::vector<std::function<bool(double)>> widgetFilters;

    auto copyWidget = [widget = w1](double value){return value > widget.GetRadius();};
    auto moveWidget = [widget = std::move(w2)](double value){return value > widget.GetRadius();};
    auto initWidget = [widget = Widget(5, 12)](double value){return value > widget.GetRadius();};

    widgetFilters.push_back(copyWidget);
    widgetFilters.push_back(moveWidget);
    widgetFilters.push_back(initWidget);

    std::vector<double> doubles(15,0);
    for (int i = 0; i != 15; ++i)
    {
        doubles[i] = i;
    }
    EvaluateFilters(doubles, widgetFilters);

}

void C6_Lambda::Bind()
{
    double m{5};
    std::vector<double> doubles1(15,0);
    std::vector<double> doubles2(15,0);
    for (int i = 0; i != 15; ++i)
    {
        doubles1[i] = i;
        doubles2[i] = i + 1;
    }

    auto copyFunction = std::bind([multiple = m](const std::vector<double>& data){for (int i = 0; i < data.size(); ++i) {std::cout << data[i] * multiple << ", ";} std::cout << std::endl;}, doubles1);
    m = 2;
    auto moveFunction = std::bind([multiple = m](const std::vector<double>& data){for (int i = 0; i < data.size(); ++i) {std::cout << data[i] * multiple << ", ";} std::cout << std::endl;}, std::move(doubles2));

    copyFunction();
    moveFunction();

    // Let's try to use bind in the same way that we might use a lambda
    // Use the STL function "all_of" to find out if all the widgets are within a certain distance of my specified point

    Widget centre(1, -1);
    auto validateDistToCentreRef = [centreRef = &centre](const Widget& widget){return widget.GetDistanceTo(*centreRef) < 10;};
    auto validateDistToCentre = [centreRef = centre](const Widget& widget){return widget.GetDistanceTo(centreRef) < 10;};

    centre = Widget(20, 20);
    std::vector<Widget> widgets = {
        Widget(1, 2),
        Widget(3, 4),
        Widget(4, 5), 
        Widget(5, -5), 
        Widget(1, 0.5),
        Widget(10, 3)
    };

    for (const auto& w : widgets) {
        auto distToCentreRef = std::bind(validateDistToCentreRef, w);
        auto distToCentre = std::bind(validateDistToCentre, w);

        std::cout << w << (distToCentreRef(w) ? " is " : " is not ") << "within ten units of the centre, " << centre << ", by reference" << std::endl;
        std::cout << w << (distToCentre(w) ? " is " : " is not ") << "within ten units of the centre, " << centre << ", by value" << std::endl;
    }

}

void C6_Lambda::GenericLambda()
{
    // Utilise the shape factory we have already specified
    // Use decltype to initialise the forwarding types
    auto shapeMaker = [](auto&&... params){return std::make_unique<Overriding::Face>(std::forward<decltype(params)>(params)...);};

    Widget* eye = new Widget(1, 0);

    auto shape1 = shapeMaker(Widget(0, 1), Widget(0, -1));
    auto shape2 = shapeMaker(eye, eye);

    shape1->Draw();
    shape2->Draw();
}