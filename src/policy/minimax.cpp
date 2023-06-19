#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

int current_player;
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
int Minimax::minimax(State *state, int depth, bool maximizingPlayer){
    if (state->game_state == WIN) {
        if (state->player == current_player)
            return 100000;
        else
            return -100000;
    }
    if (depth == 0)
    {
        if (current_player == state->player)
            return state->evaluate(0);
        else
            return -(state->evaluate(0));
        // return state->evaluate();
    }
    if (maximizingPlayer)
    {
        int value = -100000;
        for (int i = 0; i < (int)state->legal_actions.size(); i++)
        {
            State *child = state->next_state(state->legal_actions[i]);
            value = std::max(value, minimax(child, depth - 1, false));
            delete child;
        }
        return value;
    }
    else
    {
        int value = 100000;
        for (int i = 0; i < (int)state->legal_actions.size(); i++)
        {
            State *child = state->next_state(state->legal_actions[i]);
            value = std::min(value, minimax(child, depth - 1, true));
            delete child;
        }
        return value;
    }
}

Move Minimax::get_move(State *state, int depth)
{
    int value = -100000;
    current_player = state->player;
    Move best_move;
    if (!state->legal_actions.empty())
        best_move = state->legal_actions[0];
    for (int i = 0; i < (int)state->legal_actions.size(); i++)
    {
        State *child = state->next_state(state->legal_actions[i]);
        int new_value;
        new_value = minimax(child, depth - 1, false);
        if (new_value > value)
        {
            value = new_value;
            best_move = state->legal_actions[i];
        }
        delete child;
    }
    return best_move;
}