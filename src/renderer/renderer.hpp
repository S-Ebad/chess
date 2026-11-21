#pragma once

#include "engine/board.hpp"
#include "engine/piece.hpp"
#include "renderer/window.hpp"
#include "texture.hpp"
#include <array>
#include <expected>
#include <magic_enum/magic_enum.hpp>
#include <raylib.h>
#include <string>

namespace renderer {
// used a lot
using chess::Side, chess::PieceType;

class Renderer {
public:
  [[nodiscard]]
  static std::expected<Renderer, std::string> create();
  ~Renderer() = default;

  Renderer(Renderer &&) noexcept = default;

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void draw(const chess::Board &board);

  [[nodiscard]]
  bool should_close();

  constexpr Texture &operator[](Side side, PieceType type) {
    return m_pieces[*magic_enum::enum_index(side)][*magic_enum::enum_index(type)];
  }

private:
  explicit Renderer(Window window);
  [[nodiscard]]
  std::expected<void, std::string> load_pieces();

  Window m_window;
  std::array<std::array<Texture, magic_enum::enum_count<PieceType>()>,
             magic_enum::enum_count<Side>()>
      m_pieces;
};
} // namespace renderer
