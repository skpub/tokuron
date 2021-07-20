#include "ground.hpp"
#include "game.hpp"
#include <stdio.h>
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

    heap first_node;
    first_node.cost = 0;
    memcpy(first_node.ground, *gr.ichiroku, sizeof(*gr.ichiroku));
    dp_table.emplace_back(first_node);

    udlr ways = gr.move();
    for (auto &i: ways.directions) {
        gr.go(i);
        if (sign_to_ground[gr.sign()] == NULL) {
            return;
        }
    }   
}
