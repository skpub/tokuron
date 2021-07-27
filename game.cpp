#include "ground.hpp"
#include "constant.hpp"
#include "game.hpp"
#include <stdio.h>
#include <string.h>


Game::Game(ground gr) {
    this->sign_to_ground[gr.sign()] = 0;
    unsigned char tmp[N*N];
    memcpy(tmp, gr.ichiroku, sizeof(tmp));

    heap first_node;
    first_node.cost = 0;
    memcpy(first_node.ground, *gr.ichiroku, sizeof(*gr.ichiroku));
    this->dp_table.emplace_back(first_node);

    udlr ways = gr.move();
    for (auto &i: ways.directions) {
        gr.go(i);
        if (sign_to_ground[gr.sign()] == NULL) {
            return;
        }
    }   
}
