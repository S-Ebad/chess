#include "renderer.hpp"
#include "constants.hpp"
#include "engine/board.hpp"
#include "engine/piece.hpp"
#include "renderer/texture.hpp"
#include "renderer/window.hpp"
#include <cassert>
#include <cctype>
#include <cstddef>
#include <expected>
#include <filesystem>
#include <format>
#include <magic_enum/magic_enum.hpp>
#include <nanosvg.h>
#include <nanosvgrast.h>
#include <raylib.h>
#include <string>
#include <utility>

namespace fs = std::filesystem;

namespace {
void draw_board() {
  using namespace renderer;

  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      Color color = ((row + col) % 2 == 0) ? LIGHT_SQUARE : DARK_SQUARE;

      int x = col * SQUARE_SIZE;
      int y = row * SQUARE_SIZE;

      DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, color);
    }
  }
}
} // namespace

namespace renderer {
std::expected<Renderer, std::string> Renderer::create() {
  auto window = Window::create(WINDOW_SIZE, WINDOW_SIZE, "chess");
  if (!window) {
    return std::unexpected(std::move(window.error()));
  }

  Renderer renderer{std::move(*window)};

  auto res = renderer.load_pieces();
  if (!res) {
    return std::unexpected(std::move(res.error()));
  }

  return renderer;
}

Renderer::Renderer(Window window) : m_window(std::move(window)) {
}

bool Renderer::should_close() {
  return WindowShouldClose();
}

void Renderer::draw(const Board & /*_*/) {
  BeginDrawing();
  ClearBackground(WHITE);

  draw_board();

  size_t width = 0;
  size_t height = 0;

  // TODO: wait for board to implement starting position to draw it.
  // until then this will do
  for (const auto side : magic_enum::enum_values<Side>()) {
    for (const auto type : magic_enum::enum_values<PieceType>()) {
      if (type == PieceType::None) {
        continue;
      }

      const auto &texture = (*this)[side, type];
      DrawTexture(*texture, static_cast<int>(width) * SQUARE_SIZE,
                  static_cast<int>(height) * SQUARE_SIZE, RAYWHITE);

      if (++width == BOARD_SIZE) {
        width = 0;
        ++height;
      }
    }
  }

  EndDrawing();
}

std::expected<void, std::string> Renderer::load_pieces() {
  for (const auto side : magic_enum::enum_values<Side>()) {
    for (const auto type : magic_enum::enum_values<PieceType>()) {
      if (type == PieceType::None) {
        continue;
      }

      // INVARIANT: type != PieceType::None, so the optional is engaged.
      const auto symbol = *Piece::piece_symbol(type);
      const auto side_name = magic_enum::enum_name(side);

      char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(side_name[0])));
      char upper = static_cast<char>(std::toupper(symbol));

      const auto filename{std::format("{}{}.svg", lower, upper)};
      const fs::path file_path{fs::path{ASSETS_DIR} / filename};

      TextureResult result = Texture::from_file(file_path.string(), SQUARE_SIZE);

      if (!result) {
        return std::unexpected(std::move(result.error()));
      }

      (*this)[side, type] = std::move(*result);
    }
  }

  return {};
}
} // namespace renderer
