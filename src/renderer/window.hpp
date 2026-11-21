#pragma once

#include "constants.hpp"
#include <expected>
#include <raylib.h>
#include <string>
#include <utility>

namespace renderer {
// Owns the raylib window and closes it automatically. Only Renderer can create one.
class Window {
public:
  // Closes the window, unless it was moved away.
  ~Window() {
    if (m_open) {
      CloseWindow();
    }
  }

  // Takes over `other`'s window; `other` will no longer close it.
  Window(Window &&other) noexcept : m_open{std::exchange(other.m_open, false)} {
  }

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window &operator=(Window &&) = delete;

private:
  friend class Renderer; // only the renderer creates a window

  // Creates a Window that owns nothing yet; create() sets it up.
  Window() = default;

  // Opens a `width` x `height` window with the given title, capped at constants::FPS.
  // Returns the window, or an error message if raylib couldn't open it.
  [[nodiscard]]
  static std::expected<Window, std::string> create(int width, int height, const char *title) {
    InitWindow(width, height, title);

    if (!IsWindowReady()) {
      return std::unexpected("Failed to initialize raylib window");
    }

    SetTargetFPS(constants::FPS);

    Window window;
    window.m_open = true;

    return window;
  }

  bool m_open = false; // true if this object is responsible for closing the window
};
} // namespace renderer
