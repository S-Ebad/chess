#pragma once

#include <expected>
#include <raylib.h>
#include <string>
#include <utility>

namespace renderer {
class Window {
public:
  ~Window() {
    if (m_open)
      CloseWindow();
  }

  Window(Window &&other) noexcept : m_open{std::exchange(other.m_open, false)} {
  }

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window &operator=(Window &&) = delete;

private:
  friend class Renderer; // only the renderer creates a window

  Window() = default;
  static std::expected<Window, std::string> create(int width, int height, const char *title) {
    InitWindow(width, height, title);

    if (!IsWindowReady()) {
      return std::unexpected("Failed to initialize raylib window");
    }

    SetTargetFPS(60);

    Window window;
    window.m_open = true;

    return window;
  }

  bool m_open = false;
};
} // namespace renderer
