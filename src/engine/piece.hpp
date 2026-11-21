#pragma once
#include <cstdint>
#include <optional>

namespace chess {
enum class PieceType : std::uint8_t {
  None,
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King
};

enum class Side : std::uint8_t {
  White,
  Black
};

// A piece, or what's on an empty square (type None).
class Piece {
public:
  // Creates an empty square (type None).
  constexpr Piece() = default;

  // Creates a piece of the given type and side.
  constexpr Piece(PieceType type, Side side) : m_type{type}, m_side{side} {
  }

  // Returns what kind of piece this is (None for an empty square).
  [[nodiscard]]
  constexpr PieceType type() const {
    return m_type;
  }

  // Returns which side the piece belongs to. Meaningless for an empty square.
  [[nodiscard]]
  constexpr Side side() const {
    return m_side;
  }

  // Returns the lowercase letter for a piece type (p n b r q k), as used in FEN
  // and the asset file names. Returns std::nullopt for None.
  static constexpr std::optional<char> piece_symbol(PieceType type) {
    switch (type) {
    case PieceType::Pawn:
      return 'p';
    case PieceType::Knight:
      return 'n';
    case PieceType::Bishop:
      return 'b';
    case PieceType::Rook:
      return 'r';
    case PieceType::Queen:
      return 'q';
    case PieceType::King:
      return 'k';
    default:
      return std::nullopt;
    }
  }

private:
  PieceType m_type = PieceType::None;
  Side m_side = Side::White;
};
} // namespace chess
