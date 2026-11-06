#include "../include/MainPlugin.hpp"         // NOTE: crutch

#include "Core/ApplicationCore.hpp"
#include "Interfaces/IRenderer.hpp"
#include "Interfaces/Package.hpp"

#include <cassert>
#include <memory>
#include <variant>

namespace Vectoria {

extern "C" bool INIT_PACKAGE_FUNC_NAME()
{
    ApplicationCore::instance().registerInterface(IID_MAIN_PLUGIN, reinterpret_cast<void*>(&IMainPlugin::instance()));

    auto desktop = std::make_unique<Desktop>();
    ApplicationCore::instance().root()->addChild(std::move(desktop));

    return true;
}

void Desktop::render()
{
    IRenderer* renderer = nullptr;
    if (ApplicationCore::instance().queryInterface(IID_RENDERER, reinterpret_cast<void**>(&renderer)) !=
        ApplicationCore::Error::SUCCESS)
    {
        return;
    }

    renderer->clear();

    renderer->renderRect(Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF}, BoxF{ 100.0F, 100.0F, 800.0F, 800.0F }, 0.0F);  // NOTE: crutch
}

bool Desktop::processEvent(const Event& event)
{
    if (std::holds_alternative<EventQuit>(event))
    {
        ApplicationCore::instance().stop();
        return true;
    }

    return true;
}

Vec2F Desktop::mapLocalToGlobal(const Vec2F& pos) const
{
    if (parent() != nullptr)
    {
        return parent()->mapLocalToGlobal(pos);
    }
    return pos;
}

Vec2F Desktop::mapGlobalToLocal(const Vec2F& pos) const
{
    if (parent() != nullptr)
    {
        return parent()->mapGlobalToLocal(pos);
    }
    return pos;
}

IMainPlugin& IMainPlugin::instance()
{
    static IMainPlugin instance;
    return instance;
}

} // namespace Vectoria 