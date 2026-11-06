#ifndef I_SELECTION_MANAGER_HPP
#define I_SELECTION_MANAGER_HPP

#include "Utils/AObject.hpp"

namespace Vectoria {        // NOTE: это мой namespace, чтобы не конфликтовал Color с ::Color из raylib

class ISelectionManager
{
public:
    virtual ~ISelectionManager() = default;
    virtual void select(AObject* object) = 0;
    virtual void deselect(AObject* object) = 0;
    virtual void clearSelection() = 0;
    virtual const std::vector<AObject*>& getSelectedObjects() const = 0;
};

} // namespace Vectoria

#endif