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

class Piece {
public:
  constexpr Piece() = default;
  constexpr Piece(PieceType type, Side side) : m_type{type}, m_side{side} {
  }

  [[nodiscard]]
  constexpr PieceType type() const {
    return m_type;
  }

  [[nodiscard]]
  constexpr Side side() const {
    return m_side;
  }

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
