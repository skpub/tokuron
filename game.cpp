#include "ground.hpp"
#include "game.hpp"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

// GLOBAL
vector<heap> dp_table;
unordered_map<long long, int> sign_to_ground;
// -- GLOBAL

void game(ground gr) {
    udlr ways = gr.move();
    
}
