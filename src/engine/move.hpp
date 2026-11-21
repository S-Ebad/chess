#pragma once

#include "engine/square.hpp"
namespace chess {

// A move of one piece from one square to another. Captures need no special
// field: whatever stands on `to` gets replaced.
struct Move {
  Square from; // square the piece starts on
  Square to;   // square the piece ends on
};

}

