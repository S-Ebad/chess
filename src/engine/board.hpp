#pragma once

#include "piece.hpp"
#include <array>
#include <cstdint>

// clang-format off
enum class File : std::uint8_t {
  A, B, C, D, E, F, G, H
};

enum class Rank : std::uint8_t {
  R1, R2, R3, R4, R5, R6, R7, R8
};
// clang-format on

using Square = int8_t;

class Board {
public:
  Board();

  Piece operator[](File file, Rank rank) const;
  Piece operator[](Square sq) const;

private:
  std::array<Piece, 64> m_squares;
  Side m_side_to_move;
};
