#include <cstdlib>

#include "../state/state.hpp"
#include "./alpha_beta.hpp"

/*
function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
*/
int AlphaBeta::pruning_minimax(State* state, int depth, int alpha, int beta, bool maximizingPlayer) {
  if(depth == 0 || state->game_state == WIN) {
    return state->evaluate();
  }
  if(maximizingPlayer) {
    int value = -100000;
    for(int i = 0; i < state->legal_actions.size(); i++) {
      State* child = state->next_state(state->legal_actions[i]);
      value = std::max(value, pruning_minimax(child, depth - 1, alpha, beta, !maximizingPlayer));
      alpha = std::max(alpha, value);
      if(beta <= alpha) {
        return value;
      }
      delete child;
    }
    return value;
  } else {
    int value = 100000;
    for(int i = 0; i < state->legal_actions.size(); i++) {
      State* child = state->next_state(state->legal_actions[i]);
      value = std::min(value, pruning_minimax(child, depth - 1, alpha, beta, !maximizingPlayer));
      beta = std::min(beta, value);
      if(beta <= alpha) {
        return value;
      }
      delete child;
    }
    return value;
  }
}

Move AlphaBeta::get_move(State* state, int depth) {
  int value = -100000;
  Move best_move;
  if(!state->legal_actions.empty()) best_move = state->legal_actions[0];
  for(int i = 0; i < state->legal_actions.size(); i++) {
    State* child = state->next_state(state->legal_actions[i]);
    int new_value;
    if(state->player == 0) new_value = pruning_minimax(child, depth - 1, -100000, 100000, false);
    else if(state->player == 1) new_value = pruning_minimax(child, depth - 1, -100000, 100000, true);
    if(new_value > value) {
      value = new_value;
      best_move = state->legal_actions[i];
    }
    delete child;
  }
  return best_move;
}