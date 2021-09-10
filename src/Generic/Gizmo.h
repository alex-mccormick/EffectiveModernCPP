#include <memory>

class Gizmo {
    public:
        Gizmo();
        ~Gizmo();

        // This only works becauuse the .h file doesn't expose any of the private members
        // If we needed to expose "string" as part of the interface here it doesn't work.

        // We use the same structure for the move assignment and constructors
        Gizmo(Gizmo&& rhs); // rhs is a univeral reference
        Gizmo& operator=(Gizmo&& rhs);

        // And for the copy assignment and constructors, because defining the move constructor forces the copy constructors to be deleted
        Gizmo(const Gizmo& rhs);
        Gizmo& operator=(const Gizmo& rhs);

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl; // This is the absolute barebones of the pImpl idiom

        int x{5};
};