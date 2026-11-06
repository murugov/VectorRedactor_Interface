#ifndef MAIN_PLAGIN_HPP
#define MAIN_PLAGIN_HPP

#include "Interfaces/IID.hpp"
#include "Interfaces/Package.hpp"
#include "Utils/AObject.hpp"

namespace Vectoria {

constexpr static const IID IID_MAIN_PLUGIN = 100;

extern "C" InitPackageFunc INIT_PACKAGE_FUNC_NAME;

class IMainPlugin
{
private:
    IMainPlugin()  = default;
    ~IMainPlugin() = default;

public:
    IMainPlugin(const IMainPlugin&)            = delete;
    IMainPlugin(IMainPlugin&&)                 = delete;
    IMainPlugin& operator=(const IMainPlugin&) = delete;
    IMainPlugin& operator=(IMainPlugin&&)      = delete;

    static IMainPlugin& instance();
};

class Desktop final : public AObject
{
public:
    Desktop()  = default;
    ~Desktop() = default;

    void render() override;
    bool processEvent(const Event& event) override;

    Vec2F mapLocalToGlobal(const Vec2F& pos) const override final;
    Vec2F mapGlobalToLocal(const Vec2F& pos) const override final;
};

} // namespace Vectoria

#endif