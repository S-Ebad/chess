#pragma once

#include "board.hpp"

namespace chess {
class Engine {
public:
  Engine();

  [[nodiscard]]
  const Board &board() const {
    return m_board;
  }

private:
  Board m_board;
};
} // namespace chess
