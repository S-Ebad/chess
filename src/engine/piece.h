#ifndef PIECE_H
#define PIECE_H
#include <stdint.h>

typedef enum PieceType : uint8_t {
  PIECE_TYPE_NONE,
  PIECE_TYPE_PAWN,
  PIECE_TYPE_KNIGHT,
  PIECE_TYPE_BISHOP,
  PIECE_TYPE_ROOK,
  PIECE_TYPE_QUEEN,
  PIECE_TYPE_KING,
} PieceType;

typedef enum Side : uint8_t {
  SIDE_WHITE,
  SIDE_BLACK,
} Side;

typedef struct Piece {
  Side side;
  PieceType type;
} Piece;

bool piece_is_empty(Piece p);
char piece_to_char(Piece p); // Maps to 'P', 'p', ..., etc. for board_print.

#endif // PIECE_H
