#pragma once
#include <cstdint>

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

class Piece {
public:
  constexpr Piece() = default;
  constexpr Piece(PieceType type, Side side) : m_type{type}, m_side{side} {
  }

  [[nodiscard]] constexpr PieceType type() const {
    return m_type;
  }

  [[nodiscard]] constexpr Side side() const {
    return m_side;
  }

private:
  PieceType m_type = PieceType::None;
  Side m_side = Side::White;
};
