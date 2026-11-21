#include "engine/board.hpp"
#include "renderer/renderer.hpp"
#include <cstdlib>
#include <print>


int main() {
  auto renderer = renderer::Renderer::create();
  auto board = chess::Board {};

  if (!renderer) {
    std::println(stderr, "Error: {}", renderer.error());
    return EXIT_FAILURE;
  }

  while (!renderer->should_close()) {
    renderer->draw(board);
  }
}
