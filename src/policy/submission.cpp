#include <cstdlib>

#include "../state/state.hpp"
#include "./alpha_beta.hpp"

int CurrentPlayer;
int CurrentStep = 0;

int AlphaBeta::minimax(State *state, int depth, int alpha, int beta, bool maximizingPlayer) {
  if (state->game_state == WIN) {
    if (state->player == CurrentPlayer)
      return 100000;
    else
      return -100000;
  }
  if (depth == 0) {
    if (CurrentPlayer == state->player)
      return state->evaluate(CurrentStep);
    else
      return -(state->evaluate(CurrentStep));
  }
  if (maximizingPlayer) {
    int value = -100000;
    for (int i = 0; i < (int)state->legal_actions.size(); i++) {
      State *child = state->next_state(state->legal_actions[i]);
      value = std::max(value, minimax(child, depth - 1, alpha, beta, false));
      alpha = std::max(alpha, value);
      if (beta <= alpha) {
        return value;
        //break;
      }
      delete child;
    }
    return value;
  }
  else {
    int value = 100000;
    for (int i = 0; i < (int)state->legal_actions.size(); i++) {
      State *child = state->next_state(state->legal_actions[i]);
      value = std::min(value, minimax(child, depth - 1, alpha, beta, true));
      beta = std::min(beta, value);
      if(beta <= alpha){
        return value;
        //break;
      }
      delete child;
    }
    return value;
  }
}

Move AlphaBeta::get_move(State *state, int depth) {
  int value = -100000;
  CurrentPlayer = state->player;
  Move best_move;
  if (!state->legal_actions.empty())
    best_move = state->legal_actions[0];
  for (int i = 0; i < (int)state->legal_actions.size(); i++) {
    State *child = state->next_state(state->legal_actions[i]);
    int new_value;
    new_value = minimax(child, depth - 1, -100000, 100000, false);
    if (new_value > value) {
      value = new_value;
      best_move = state->legal_actions[i];
    }
    delete child;
  }
  CurrentStep += 2;
  return best_move;
}