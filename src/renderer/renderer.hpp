#pragma once

#include <array>
#include <raylib.h>
#include "engine/board.hpp"

class Renderer {
public:
  Renderer();
  ~Renderer();

  Renderer(const Renderer &) = delete;
  Renderer(Renderer &&) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void draw(const Board &board);
  [[nodiscard]] bool should_close();

private:
  std::array<std::array<Texture2D, 7>, 2> m_pieces;
};
