#include "Chapters.h"
#include "../Generic/Gizmo.h"

C4b_PImpl::C4b_PImpl()
    : BookChapter("PImpl") {
    this->menuMap["PImpl"] = (BookChapter::MenuFunction) &(C4b_PImpl::PImpl);
}


void C4b_PImpl::PImpl() {

    Gizmo g1; // We need the destructor to be declared in the .h, and defined in the .cpp

    Gizmo g2(std::move(g1)); // We have declared a destructor, so the compiler will not generate the move constructor

    g1 = g2; // This is copy assignment, but it needs to be manually defined because manually defining the move constructor causes the compiler to delete the copy constructor

}