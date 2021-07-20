#include <stdio.h>
#include "ground.hpp"
#include "game.hpp"

int main() {
    // ground gr({15,2,6,3,4,5,0,7,1,9,10,11,8,13,12,14}); 
    ground gr({ 9, 0, 6, 3,
                4, 5, 10,7,
                8, 1, 14,11,
                12,13,2 ,15}); 
    printf("size: %lu\n", sizeof(gr));
    // printf("cost: %d\n", gr.manhattandistance());
    // printf("fst, sign: %llu\n", gr.sign());
    // gr.view();
    // gr.move().view();
    // gr.d();
    // gr.view();
    // printf("cost: %d\n", gr.manhattandistance());
    // printf("fst, sign: %llu\n", gr.sign());
    gr.spotfinder();
    udlr v = gr.move();
    v.view();
    // gr.view();
    printf("___-----game start-----_____\n");
    game(gr);
    return 0;
}