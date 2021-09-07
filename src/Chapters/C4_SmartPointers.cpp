#include "Chapters.h"
#include "../Generic/Widget.h"

C4_SmartPointers::C4_SmartPointers()
    : BookChapter("SmartPointers") {
    this->menuMap["ResourceOwnership"] = (BookChapter::MenuFunction) &(C4_SmartPointers::ResourceOwnership);
}

void C4_SmartPointers::ResourceOwnership() {
    
    std::cout << "Use unique-ptr for exclusive-ownership" << std::endl;

    // Factory functions can (should) return unique_ptr
    {
        std::cout << "Make a shape within this scope" << std::endl;
        auto u_ptr = shape_factory(ShapeType::Shape);
        std::cout << "Destroy the shape by ending the scope" << std::endl;
    }

    // A custom deleter can be specified
    {
        std::cout << "Make a face within this scope" << std::endl;
        auto u_ptr_d = shape_factory_with_deleter(ShapeType::Face, new Widget(1,1), new Widget(2,2));
        std::cout << "Destroy the face by ending the scope" << std::endl;
    }


}