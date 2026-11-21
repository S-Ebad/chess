#pragma once

#include "board.hpp"

namespace chess {
// Owns the game: the board and, later, the rules (legal moves, check, game over).
class Engine {
public:
  // Starts a new game from the standard starting position, White to move.
  Engine();

  // Returns the current board, read-only (e.g. for the renderer to draw).
  [[nodiscard]]
  const Board &board() const {
    return m_board;
  }

private:
  Board m_board;
};
} // namespace chess
