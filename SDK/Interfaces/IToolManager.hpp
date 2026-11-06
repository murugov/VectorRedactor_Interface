#ifndef I_TOOL_MANAGER_HPP
#define I_TOOL_MANAGER_HPP

#include "Interfaces/ITool.hpp"

namespace Vectoria {
    
class IToolManager
{
public:
    IToolManager()          = default;
    virtual ~IToolManager() = default;

    enum class Error;

    virtual Error addTool(ITool* tool)          = 0;
    virtual Error removeTool(ToolID tool_id)    = 0;
    virtual void* activeTool() const            = 0;
    virtual Error setActiveTool(ToolID tool_id) = 0;
};

enum class IToolManager::Error
{
    SUCCESS,
    INVALID_ARGS,

    TOOL_NOT_FOUND,
};

} // namespace Vectoria

#endif