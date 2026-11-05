#ifndef RENDERER_CONSTANTS_H
#define RENDERER_CONSTANTS_H
#include <raylib.h>

static constexpr int BOARD_SIZE = 8;
static constexpr int SQUARE_SIZE = 80;
static constexpr int WINDOW_SIZE = BOARD_SIZE * SQUARE_SIZE;

static constexpr Color LIGHT_SQUARE = {240, 217, 181, 255};
static constexpr Color DARK_SQUARE = {181, 136, 99, 255};

#endif // RENDERER_CONSTANTS_H

