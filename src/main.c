#include <raylib.h>
#include <stddef.h>

static constexpr int BOARD_SIZE = 8;
static constexpr int SQUARE_SIZE = 80;
static constexpr int WINDOW_SIZE = BOARD_SIZE * SQUARE_SIZE;

static constexpr Color LIGHT_SQUARE = {240, 217, 181, 255};
static constexpr Color DARK_SQUARE = {181, 136, 99, 255};

static void draw_board(void) {
  for (int rank = 0; rank < BOARD_SIZE; rank++) {
    for (int file = 0; file < BOARD_SIZE; file++) {
      const Color color = (rank + file) % 2 == 0 ? LIGHT_SQUARE : DARK_SQUARE;

      DrawRectangle(file * SQUARE_SIZE, rank * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, color);
    }
  }
}

int main(void) {
  InitWindow(WINDOW_SIZE, WINDOW_SIZE, "chess");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // logic

    BeginDrawing();
    // drawing

    ClearBackground(BLACK);
    draw_board();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
