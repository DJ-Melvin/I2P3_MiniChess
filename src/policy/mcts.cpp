#include <cstdlib>

#include "../state/state.hpp"
#include "./mcts.hpp"

using namespace std;

// Path: src\policy\mcts.cpp
// Compare this snippet from src\policy\mcts.hpp:
// #pragma once
// #include "../state/state.hpp"
//
// class MCTS{
// public:
//     MCTS(State* state);
//     ~MCTS();
//     void run();
//     void print();
// private:
//     State* state;
// };
