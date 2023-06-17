#pragma once
#include "../state/state.hpp"

class Minimax{
public:
  static int minimax(State* state, int depth, bool maximizingPlayer);
  static Move get_move(State* state, int depth);
};