#pragma once

#include <raylib.h>
#include <string_view>

namespace renderer {
constexpr int BOARD_SIZE = 8;
constexpr int SQUARE_SIZE = 80;
constexpr int WINDOW_SIZE = BOARD_SIZE * SQUARE_SIZE;

constexpr Color LIGHT_SQUARE = {240, 217, 181, 255};
constexpr Color DARK_SQUARE = {181, 136, 99, 255};

// CHESS_ASSETS_DIR is set by CMake to the absolute path of the source tree's assets/ folder
inline constexpr std::string_view ASSETS_DIR = CHESS_ASSETS_DIR;
} // namespace renderer
