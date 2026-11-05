#ifndef RENDERER_H
#define RENDERER_H
#include <raylib.h>
#include "engine/board.h"

typedef struct Renderer {
  Texture2D pieces[2][7];   // [side][type], or one sprite sheet
} Renderer;

void renderer_init(Renderer *renderer); // initializes raylib, loades textures, sets target fps
void renderer_shutdown(Renderer *renderer); // unload textures, and close window

bool renderer_should_close(void); // wraps WindowShouldClose
void renderer_draw(const Renderer *renderer, const Board *board);

#endif // RENDERER_H
