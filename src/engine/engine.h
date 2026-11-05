#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"

typedef struct Engine {
  Board board;
} Engine;

// initialize engine state & board state
void engine_init(Engine *engine);

#endif // ENGINE_H


