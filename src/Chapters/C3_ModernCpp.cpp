#include "Chapters.h"
#include "../Generic/Widget.h"
#include <set>

C3_ModernCpp::C3_ModernCpp()
    : BookChapter("ModernCpp")
{
    this->menuMap["TuplesAndEnums"] = (BookChapter::MenuFunction) & (C3_ModernCpp::TuplesAndEnums);
    this->menuMap["Overriding"] = (BookChapter::MenuFunction) & (C3_ModernCpp::Overriding);
    this->menuMap["MemberFunctionQualifiers"] = (BookChapter::MenuFunction) & (C3_ModernCpp::MemberFunctionQualifiers);
    this->menuMap["BuilderFunction"] = (BookChapter::MenuFunction) & (C3_ModernCpp::BuilderFunction);
    this->menuMap["Constexpr"] = (BookChapter::MenuFunction) & (C3_ModernCpp::ConstexprDemo);
    this->menuMap["SpecialMemberFunctions"] = (BookChapter::MenuFunction) & (C3_ModernCpp::RuleOfThree);
}

using UserInfo = std::tuple<std::string, std::string, int>;
enum UIFields
{
    uiName,
    uiEmail,
    uiScore
};

enum class UIFieldsClass
{
    uiName,
    uiEmail,
    uiScore
};

template <typename E>
constexpr auto getType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

void C3_ModernCpp::TuplesAndEnums()
{
    UserInfo uInfo;

    std::get<0>(uInfo) = "John Smith";
    std::get<getType(UIFieldsClass::uiEmail)>(uInfo) = "js@me.com";
    std::get<uiScore>(uInfo) = 20;

    std::cout << std::get<uiName>(uInfo) << " scored " << std::get<getType(UIFieldsClass::uiScore)>(uInfo) << " points, send him an email at " << std::get<uiEmail>(uInfo) << std::endl;
}

void C3_ModernCpp::Overriding()
{

    std::cout << "Base shape" << std::endl;
    auto base_shape = std::make_unique<Overriding::Shape>();
    base_shape->Draw();
    std::cout << std::endl;

    std::cout << "Base circle" << std::endl;
    auto base_circle = std::make_unique<Overriding::Circle>();
    base_circle->Draw();
    std::cout << std::endl;

    std::cout << "Face" << std::endl;
    auto face = std::make_unique<Overriding::Face>();
    face->Draw();
    std::cout << std::endl;
}

Overriding::Face make_face()
{
    return Overriding::Face();
}
Overriding::Face make_face(Widget *w1, Widget *w2)
{
    return Overriding::Face(w1, w2);
}

void C3_ModernCpp::MemberFunctionQualifiers()
{

    std::cout << "Calling eyes member function on lvalue reference" << std::endl;
    Widget *leftEye = new Widget(-0.3, 0.3);
    Widget *rightEye = new Widget(0.3, 0.3);
    Overriding::Face f1 = make_face();
    auto eyes = f1.GetEyes();

    std::cout << "Calling eyes member function on rvalue reference" << std::endl;
    auto defaultEyes = make_face().GetEyes();

    delete leftEye;
    delete rightEye;

    std::cout << "Getting eye spacing on lvalue reference (another member function)" << std::endl;
    auto spacing = f1.GetSpacing();

    // This won't compile because the function has been deleted
    // auto defaultSpacing = make_face().GetSpacing();
}

void C3_ModernCpp::BuilderFunction()
{
    Overriding::FaceBuilder fb;
    Widget *leftEye = new Widget(-0.3, 0.3);
    Widget *rightEye = new Widget(0.3, 0.3);

    Overriding::Face *face1 = fb.withLeftEye(leftEye).withRightEye(rightEye).build();
    std::cout << "We made a face using an rvalue" << std::endl;

    Overriding::Face *face2 = fb.withLeftEyeLValue(leftEye).withRightEyeLValue(rightEye).build();
    std::cout << "We made a face using an lvalue" << std::endl;

    Overriding::FaceBuilder fb2 = fb.withLeftEye(leftEye);
    Overriding::Face *face3 = fb2.build();
}

void C3_ModernCpp::ConstexprDemo()
{

    // We successfully set up an array with a const length
    constexpr Widget test{-3, 5};
    double *quadrants = new double[test.GetQuadrant()];

    std::cout << "Created an array at compile-time which is " << test.GetQuadrant() << " elements long" << std::endl;
    delete[] quadrants;
}

void C3_ModernCpp::RuleOfThree()
{

    // Widget does not have a copy or a move assignment operator
    Widget w1(4, 5);

    Widget w2{3, 2}; // Braces are ok too

    std::cout << "Attempting to use copy assignment on w2" << std::endl;
    // w2 = w1; // Compiler error; copy assignment not defined
    std::cout << "Attempting to use move assignment on w2" << std::endl;
    // w2 = std::move(w1); // Compiler error; move assignment not defined

    std::cout << "Attempting to use move constructor on w3" << std::endl;
    Widget w3(std::move(w1)); // Move constructor IS defined!!
}