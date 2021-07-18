#include "ground.hpp"
#include <stdio.h>
#include <string.h>

std::pair<unsigned char, unsigned char>
split(unsigned char v) {
    return std::make_pair(v % 4, v / 4);
}

ground::ground(unsigned char (&&ichiroku)[16]) {
    this->ichiroku = &ichiroku;
}

unsigned long long
ground::sign() {
    unsigned long long sign = 0;
    int shift = 0;
    for (int i = 0; i < 16; i++) {
        sign += (*this->ichiroku)[i] << shift;
        shift += 4;
    }
    return sign;
}

/////// move ///////////
udlr
ground::move() {
    bool u = ! (spot < 4);
    bool d = ! (spot > 11);
    bool l = ! (spot % 4 == 0);
    bool r = ! (spot % 4 == 3);
    return udlr {u, d, l, r};
}

template <typename T> void
swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

void
ground::u() {
    unsigned char index = spot - 4;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot - 4;
}

void
ground::d() {
    unsigned char index = spot + 4;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot + 4;
}

void
ground::l() {
    unsigned char index = spot - 1;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot - 1;
}

void
ground::r() {
    unsigned char index = spot + 1;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot + 1;
}
/////////////////// move

int
ground::manhattandistance() {
    int sum = 0;
    for (int i = 0; i < 16; i++) {
        std::pair<unsigned char, unsigned char> now = split(i);
        std::pair<unsigned char, unsigned char> proper = split((*ichiroku)[i]);
        sum += abs(now.first - proper.first) + abs(now.second - proper.second);
    }
    return sum;
}

void
ground::view() {
    for (int i = 0; i < 16; i++) {
        if      (i % 4 == 3)    printf("%3d\n", (*ichiroku)[i]);
        else                    printf("%3d ", (*ichiroku)[i]);
    }
    printf("spot: ichiroku[%d] = %d\n", this->spot, (*this->ichiroku)[this->spot]);
}

void
udlr::view() {
    printf("{ ");
    if (u) printf("u ");
    if (d) printf("d ");
    if (l) printf("l ");
    if (r) printf("r ");
    printf("}\n");
}

void
ground::spotfinder() {
    int cost[16] = {__INT_MAX__};

    // temp saving.
    // !!! destructive(this->ichiroku) !!!
        unsigned char (*def16)[16] = this->ichiroku;

        unsigned char tmp16[16];
        this->ichiroku = &tmp16;
    //
    int i = 0;
    for (; i < 16; i++) { // each "value of i" is a spot candidate.
        // (re)set (this->ichiroku, this->spot)
            memcpy(tmp16, *def16, sizeof(*def16));
            this->spot = i;
        //
        if ((*this->ichiroku)[i] != i) {
            int value = (*this->ichiroku)[i];
            int index = i;
            auto pos_index = split(index);
            auto pos_value = split(value);
            std::pair<char, char> move_vector = std::make_pair(
                pos_value.first     - pos_index.first,
                pos_value.second    - pos_index.second);

            // move.
            while (move_vector.first != 0) {   // x axis
                if (move_vector.first > 0)  {
                    this->r(); 
                    move_vector.first--;
                }
                else {
                    this->l();
                    move_vector.first++;
                }
            }
            while (move_vector.second != 0) {  // y axis
                if (move_vector.second > 0) {
                    this->d();
                    move_vector.second--;
                }
                else {
                    this->u();
                    move_vector.second++;
                }
            }
        }
        if (this->is_Even_DESTRUCTIVE()) cost[i] = this->manhattandistance();
    }   // -- checked each i is wheather spot or not.

    int min_cost = __INT_MAX__;
    for (int i = 0; i < 16; i++) {
        if (cost[i] < min_cost) {
            min_cost = cost[i];
            spot = i;
        }
    }
    this->ichiroku = def16;
    this->view();
    //     if (this->is_Even_DESTRUCTIVE()) goto set;
    // }   // -- checked each i is wheather spot or not.

    // set:
    //     spot = i;
    //     this->ichiroku = def16;
}

bool
ground::is_Even_DESTRUCTIVE() {
    bool even = true;
    unsigned char v_to_i[16];
    for (int i = 0; i < 16; i++) v_to_i[(*this->ichiroku)[i]] = i;

    for (int i = 0; i < 16; i++) {
        if (i == spot)                  continue; 
        if (i == (*this->ichiroku)[i])  continue;
        // "i" is not "v" (of i).
        unsigned char tmp = (*this->ichiroku)[i];
        swap(&(*this->ichiroku)[i], &(*this->ichiroku)[v_to_i[i]]);
        swap(v_to_i + i, v_to_i + tmp);
        even = !even;
    }
    return even;
}
