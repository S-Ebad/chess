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

// Draws the game: owns the window and the piece textures.
class Renderer {
public:
  // Opens the window and loads all piece textures.
  // Returns the renderer, or an error message if either step fails.
  [[nodiscard]]
  static std::expected<Renderer, std::string> create();
  ~Renderer() = default;

  Renderer(Renderer &&) noexcept = default;

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  // Draws one frame: the squares, then the pieces on `board`.
  // For now `board` is ignored and every piece texture is drawn in a row as a
  // placeholder, until Board can load a position.
  void draw(const chess::Board &board);

  // Returns true once the user has asked to close the window.
  [[nodiscard]]
  bool should_close();

  // Returns the texture for a piece, e.g. (*this)[Side::White, PieceType::Knight].
  constexpr Texture &operator[](Side side, PieceType type) {
    return m_pieces[*magic_enum::enum_index(side)][*magic_enum::enum_index(type)];
  }

private:
  // Takes ownership of an already-open window. Textures aren't loaded yet; use create() instead.
  explicit Renderer(Window window);

  // Loads a texture for every side and piece type (except None).
  // Returns an error message if any texture fails to load.
  [[nodiscard]]
  std::expected<void, std::string> load_pieces();

  Window m_window;
  // Indexed by [side][piece type]; the None column stays empty.
  std::array<std::array<Texture, magic_enum::enum_count<PieceType>()>,
             magic_enum::enum_count<Side>()>
      m_pieces;
};
} // namespace renderer
