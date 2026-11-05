#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <stdint.h>

typedef enum CastlingRights {
  CASTLE_WHITE_KING = 1,
  CASTLE_WHITE_QUEEN = 2,
  CASTLE_BLACK_KING = 4,
  CASTLE_BLACK_QUEEN = 8,
} CastlingRights;

typedef int8_t Square; // 0..63, a1=0; -1=none

typedef struct Board {
  Piece squares[64];

  Side side_to_move;
  uint8_t castling_rights : 4;
  Square en_passant_square; // -1 if none

  uint8_t halfmove_clock;
  uint16_t fullmove_number;
} Board;

void board_init(Board *board);

Piece board_get_piece(const Board *board, Square square);
void board_set_piece(Board *board, Square square, Piece p);

// for debugging
void board_print(const Board *board);

#endif // BOARD_H
