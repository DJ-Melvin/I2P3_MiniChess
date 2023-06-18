#pragma once
#include "../state/state.hpp"

class AlphaBeta{
public:
  static int minimax(State* state, int depth, int alpha, int beta, bool maximizingPlayer);
  static Move get_move(State* state, int depth);
};