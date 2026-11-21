#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

namespace chess {
// clang-format off
enum class File : std::uint8_t {
  A, B, C, D, E, F, G, H
};

enum class Rank : std::uint8_t {
  R1, R2, R3, R4, R5, R6, R7, R8
};

enum class Square : std::uint8_t {
  A1, B1, C1, D1, E1, F1, G1, H1,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A8, B8, C8, D8, E8, F8, G8, H8
};
// clang-format on

// Square layout: index = rank * 8 + file, so a1 = 0, b1 = 1, ..., h1 = 7, a2 = 8, ..., h8 = 63.
// Every function below relies on this layout.

// Returns the square where a file and rank meet, e.g. (File::E, Rank::R4) -> Square::E4.
constexpr Square make_square(File file, Rank rank);

// Returns the file (column) of a square, e.g. Square::E4 -> File::E.
constexpr File file_of(Square sq);

// Returns the rank (row) of a square, e.g. Square::E4 -> Rank::R4.
constexpr Rank rank_of(Square sq);

// Returns the square's index into a 64-element array (0 for a1 to 63 for h8).
constexpr std::size_t to_index(Square sq);

// Returns the square `df` files and `dr` ranks away from `sq`, e.g.
// offset(E4, 1, 2) -> F6 (a knight jump), offset(E4, 0, -1) -> E3.
// Positive df moves toward the h-file, positive dr toward rank 8.
//
// Returns std::nullopt if the result would leave the board. Moves must not wrap
// around the edge: H4 one file to the right is off the board, not A5.
std::optional<Square> offset(Square sq, int df, int dr);

} // namespace chess
