#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

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
int Minimax::minimax(State* state, int depth, bool maximizingPlayer) {
  if(depth == 0 || state->game_state != UNKNOWN) {
    return state->evaluate(maximizingPlayer);
  }
  if(maximizingPlayer) {
    int value = -100000;
    for(int i = 0; i < state->legal_actions.size(); i++) {
      State* child = state->next_state(state->legal_actions[i]);
      value = std::max(value, minimax(child, depth - 1, !maximizingPlayer));
      delete child;
    }
    return value;
  } else {
    int value = 100000;
    for(int i = 0; i < state->legal_actions.size(); i++) {
      State* child = state->next_state(state->legal_actions[i]);
      value = std::min(value, minimax(child, depth - 1, !maximizingPlayer));
      delete child;
    }
    return value;
  }
}

Move Minimax::get_move(State* state, int depth) {
  int value = -100000;
  Move best_move;
  if(!state->legal_actions.empty()) best_move = state->legal_actions[0];
  for(int i = 0; i < state->legal_actions.size(); i++) {
    State* child = state->next_state(state->legal_actions[i]);
    int new_value;
    if(state->player == 0) new_value = minimax(child, depth - 1, false);
    else if(state->player == 1) new_value = minimax(child, depth - 1, true);
    if(new_value > value) {
      value = new_value;
      best_move = state->legal_actions[i];
    }
    delete child;
  }
  return best_move;
}