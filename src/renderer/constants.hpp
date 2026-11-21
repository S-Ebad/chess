#pragma once

#include "engine/constants.hpp"
#include <raylib.h>
#include <string_view>

namespace renderer::constants {
using chess::constants::BOARD_SIZE;

constexpr int SQUARE_SIZE = 80;
constexpr int WINDOW_SIZE = BOARD_SIZE * SQUARE_SIZE;

constexpr Color LIGHT_SQUARE = {.r = 240, .g = 217, .b = 181, .a = 255};
constexpr Color DARK_SQUARE = {.r = 181, .g = 136, .b = 99, .a = 255};

constexpr int FPS = 60;

// CHESS_ASSETS_DIR is set by CMake to the absolute path of the source tree's assets/ folder
inline constexpr std::string_view ASSETS_DIR = CHESS_ASSETS_DIR;
} // namespace renderer::constants
