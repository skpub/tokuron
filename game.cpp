#include "ground.hpp"
#include "game.hpp"
#include <vector>
#include <unordered_map>
#include <string.h>


using std::vector;
using std::unordered_map;

// GLOBAL
vector<heap> dp_table;
unordered_map<long long, int> sign_to_ground;
// -- GLOBAL

void game(ground gr) {
    sign_to_ground[gr.sign()] = 0;
    unsigned char tmp[16];
    memcpy(tmp, gr.ichiroku, sizeof(tmp));
    dp_table[0] = heap {NULL, 0, 0, NULL};

    udlr ways = gr.move();
    for (auto &i: ways.directions) {

    }   
}
