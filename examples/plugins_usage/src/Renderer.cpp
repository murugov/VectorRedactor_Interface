#include "../include/Renderer.hpp"      // NOTE: crutch

#include "Core/ApplicationCore.hpp"
#include "Interfaces/IInputPump.hpp"
#include "Interfaces/IRenderer.hpp"
#include "Interfaces/Package.hpp"
#include "Utils/Event.hpp"

#include <raylib.h>
#include <cassert>
#include <optional>
#include <limits>

namespace Vectoria {

#define LOG_NOT_IMPLEMENTED()                                                                                 \
    do {                                                                                                       \
        ApplicationCore::log(ApplicationCore::LogLevel::ERROR, "FIXME: %s is not implemented yet", __func__); \
    } while (0)

extern "C" bool INIT_PACKAGE_FUNC_NAME() {
    ApplicationCore::instance().registerInterface(
        IID_RENDERER, reinterpret_cast<void*>(static_cast<IRenderer*>(&Renderer::instance()))
    );
    ApplicationCore::instance().registerInterface(
        IID_INPUT_PUMP, reinterpret_cast<void*>(static_cast<IInputPump*>(&Renderer::instance()))
    );

    return true;
}

void Renderer::openWindow(const Vec2F& size) {
    ::InitWindow(static_cast<int>(size.x()), static_cast<int>(size.y()), "Vectoria");
    
    ::SetTraceLogLevel(::LOG_WARNING); 
    
    is_window_open_ = true;
}

void Renderer::closeWindow() {
    if (is_window_open_) {
        ::CloseWindow();
        is_window_open_ = false;
    }
}

/* ------------------ public methods ------------------ */

Renderer::Renderer() {
    const Vec2F window_size = { 1000.0F, 1000.0F };
    openWindow(window_size);
    
    ApplicationCore::log(ApplicationCore::LogLevel::OK, "Graphics (raylib) initialized successfully");
}

Renderer::~Renderer() {
    closeWindow();
    ApplicationCore::log(ApplicationCore::LogLevel::OK, "Graphics deinitialized successfully");
}

Renderer& Renderer::instance() {
    static Renderer instance;
    return instance;
}

void Renderer::renderRect(const Color& color, const BoxF& box, float angle) {
    ::Color ray_color = { color.r, color.g, color.b, color.a };


    Rectangle rect = { box.left(), box.top(), box.size().x(), box.size().y() };
    if (std::abs(angle) > std::numeric_limits<float>::epsilon()) {
        Vector2 origin = { 0.0F, 0.0F };
        ::DrawRectanglePro(rect, origin, angle, ray_color);
    }
    else {
        ::DrawRectangleRec(rect, ray_color);
    }
}

void Renderer::renderEllipse(const Color& color, const BoxF& box) {
    ::Color ray_color = { color.r, color.g, color.b, color.a };
    
    float radius_x = box.size().x() / 2.0F;
    float radius_y = box.size().y() / 2.0F;
    float center_x = box.left() + radius_x;
    float center_y = box.top() + radius_y;

    ::DrawEllipse(static_cast<int>(center_x), static_cast<int>(center_y), radius_x, radius_y, ray_color);
}

void Renderer::renderCircle(const Color& color, const BoxF& box) {
    renderEllipse(color, box);
}

void Renderer::clear() {
    ::BeginDrawing();
    ::ClearBackground(::Color{ 0, 0, 0, 0 });
}

void Renderer::update() {
    ::EndDrawing();
}

std::optional<Event> Renderer::pollEvent() {
    if (::WindowShouldClose()) {
        return EventQuit();
    }

    static Vector2 last_mouse_pos = { 0, 0 };
    Vector2 current_mouse_pos = ::GetMousePosition();
    if (current_mouse_pos.x != last_mouse_pos.x || current_mouse_pos.y != last_mouse_pos.y) {
        last_mouse_pos = current_mouse_pos;
        return EventMouse(EventMouse::Type::MOTION, Vec2F{current_mouse_pos.x, current_mouse_pos.y});
    }

    if (::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return EventMouse(EventMouse::Type::LEFT_BUTTON_PRESSING, Vec2F{current_mouse_pos.x, current_mouse_pos.y});
    }

    if (::IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        return EventMouse(EventMouse::Type::LEFT_BUTTON_RELEASING, Vec2F{current_mouse_pos.x, current_mouse_pos.y});
    }

    return std::nullopt;
}

/* Stubs */

IRenderer::ResourceID Renderer::loadTexture([[maybe_unused]] const char* path) {
    LOG_NOT_IMPLEMENTED();
    return static_cast<ResourceID>(0);
}

IRenderer::FontID Renderer::loadFont([[maybe_unused]] const char* filename) {
    LOG_NOT_IMPLEMENTED();
    return static_cast<FontID>(0);
}

void Renderer::renderRectLines([[maybe_unused]] const Color& color, [[maybe_unused]] const BoxF& box, [[maybe_unused]] float angle) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderEllipseLines([[maybe_unused]] const Color& color, [[maybe_unused]] const BoxF& box) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderLine([[maybe_unused]] const Vec2F& origin, [[maybe_unused]] const Vec2F& end, [[maybe_unused]] const Color& color) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderVector([[maybe_unused]] const Vec2F& origin, [[maybe_unused]] const Vec2F& vector, [[maybe_unused]] const Color& color) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderPixel([[maybe_unused]] const Vec2F& pos, [[maybe_unused]] const Color& color) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderTexture([[maybe_unused]] const ResourceID& texture, [[maybe_unused]] const BoxF& box, [[maybe_unused]] float angle) {
    LOG_NOT_IMPLEMENTED();
}

void Renderer::renderText([[maybe_unused]] const char* text, [[maybe_unused]] const Color& color,
                           [[maybe_unused]] const BoxF& box, [[maybe_unused]] const FontID& font_id,
                           [[maybe_unused]] int font_size)
{
    LOG_NOT_IMPLEMENTED();
}

} // namespace Vectoria