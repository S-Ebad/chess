#pragma once

#include "engine/board.hpp"
#include <array>
#include <expected>
#include <raylib.h>
#include <string>

namespace renderer {
class Renderer {
public:
  static std::expected<Renderer, std::string> create();
  ~Renderer();

  Renderer(Renderer &&) noexcept;

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void draw(const Board &board);
  [[nodiscard]] bool should_close();

private:
  Renderer();

  std::array<std::array<Texture, 7>, 2> m_pieces;
  bool m_owns_window {true}; // if moved-from, shouldn't close window
};
} // namespace renderer
