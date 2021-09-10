#include "Gizmo.h"
#include "Widget.h"
#include <string>

struct Gizmo::Impl {
    std::string name;
    Widget vertex{0, 2};
    Widget centre{2, 1};
};

Gizmo::Gizmo() : pImpl(std::make_unique<Impl>()) {
    std::cout << "Gizmo initialised using default constructor to default value of " << x << std::endl;
}

Gizmo::~Gizmo() = default;
Gizmo& Gizmo::operator=(Gizmo&& rhs) = default;
Gizmo::Gizmo(Gizmo&& rhs) = default;

// These cannot be defined default because the unique_ptr cannot be copied
Gizmo& Gizmo::operator=(const Gizmo& rhs)
{
    // Both this and rhs could be nullptr
    if (!rhs.pImpl)
    {
        // Reset because the rhs is null
        pImpl.reset();
    }
    else if (!pImpl)
    {
        // Current is null, directly assign
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
    }
    else
    {
        // Direct assign
        *pImpl = *rhs.pImpl;
    }
    return *this;
}
Gizmo::Gizmo(const Gizmo& rhs)
    : pImpl(nullptr)
{
    if (rhs.pImpl)
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
}