#include "Chapters.h"

C4_SmartPointers::C4_SmartPointers() {
    this->menuMap["ResourceOwnership"] = (BookChapter::MenuFunction) &(C4_SmartPointers::ResourceOwnership);
}

void C4_SmartPointers::ResourceOwnership() {
    
    std::cout << "Use unique-ptr for exclusive-ownership" << std::endl;

}