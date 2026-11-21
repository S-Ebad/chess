#pragma once

#include "engine/constants.hpp"
#include "engine/move.hpp"
#include "engine/square.hpp"
#include "piece.hpp"
#include <array>
#include <expected>
#include <string>
#include <string_view>

namespace chess {
// The pieces on the board and whose turn it is.
class Board {
public:
  // Creates an empty board with White to move.
  Board() : m_squares{} {
  }

  // Builds a board from a FEN string, e.g. the starting position:
  //   "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
  //
  // Field 1 lists the pieces rank by rank, from rank 8 down to rank 1, with
  // ranks separated by '/'. Within a rank it goes from the a-file to the h-file.
  // Uppercase letters are White, lowercase are Black (p n b r q k), and a digit
  // 1-8 means that many empty squares in a row.
  // Field 2 is the side to move: 'w' or 'b'.
  // The remaining fields (castling, en passant, move counters) can be ignored for now.
  //
  // Returns the board, or an error message if the string is malformed (unknown
  // letter, a rank that doesn't add up to 8 squares, not exactly 8 ranks, a bad side to move).
  [[nodiscard]]
  static std::expected<Board, std::string> from_fen(std::string_view fen);

  // Returns the piece on the given file and rank (a piece of type None if the square is empty).
  Piece operator[](File file, Rank rank) const;

  // Returns the piece on the given square (a piece of type None if the square is empty).
  Piece operator[](Square sq) const;

  // Plays a move without checking whether it's legal (for now):
  // moves the piece on `from` to `to`, replacing anything there (a capture),
  // empties `from`, then switches the side to move.
  void make_move(const Move &move);

private:
  std::array<Piece, constants::SQUARE_COUNT> m_squares; // indexed with to_index(Square)
  Side m_side_to_move = Side::White;                    // whose turn it is
};
} // namespace chess
