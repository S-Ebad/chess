#pragma once

#include "engine/constants.hpp"
#include "piece.hpp"
#include <array>
#include <cstdint>

namespace chess {
// clang-format off
enum class File : std::uint8_t {
  A, B, C, D, E, F, G, H
};

enum class Rank : std::uint8_t {
  R1, R2, R3, R4, R5, R6, R7, R8
};
// clang-format on

using Square = int8_t;

// The pieces on the board and whose turn it is.
class Board {
public:
  // Creates an empty board with White to move.
  Board() : m_squares{} {
  }

  // Returns the piece on the given file and rank (a piece of type None if the square is empty).
  Piece operator[](File file, Rank rank) const;

  // Returns the piece on the given square (a piece of type None if the square is empty).
  Piece operator[](Square sq) const;

private:
  std::array<Piece, constants::SQUARE_COUNT> m_squares;
  Side m_side_to_move = Side::White; // whose turn it is
};
} // namespace chess
