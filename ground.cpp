#include "ground.hpp"
#include "constant.hpp"
#include <stdio.h>
#include <string.h>

std::pair<unsigned char, unsigned char>
split(unsigned char v) {
    return std::make_pair(v % N, v / N);
}

ground::ground(unsigned char (&&ichiroku)[N*N]) {
    this->ichiroku = &ichiroku;
}

unsigned long long
ground::sign() {
    unsigned long long sign = 0;
    int shift = 0;
    for (int i = 0; i < N*N; i++) {
        sign += (unsigned long long)((*this->ichiroku)[i]) << shift;
        shift += N;
    }
    return sign;
}

/////// move ///////////
udlr
ground::move() {
    std::set<udlr2> ret;
    if ( ! (spot < N)   )       ret.insert(udlr2::u);
    if ( ! (spot > N*(N-1)-1))  ret.insert(udlr2::d);
    if ( ! (spot % N == 0))     ret.insert(udlr2::l);
    if ( ! (spot % N == N-1))   ret.insert(udlr2::r);
    return udlr { ret };
}

template <typename T> void
swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

void
ground::u() {
    unsigned char index = spot - N;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot - N;
}

void
ground::d() {
    unsigned char index = spot + N;
    swap(&(*ichiroku)[spot], &(*ichiroku)[index]);
    spot = spot + N;
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

void
ground::go(udlr2 v) {
    switch (v) {
        case udlr2::u:
            u();
            break;
        case udlr2::d:
            d();
            break;
        case udlr2::l:
            l();
            break;
        case udlr2::r:
            r();
            break;
    }
}

/////////////////// move

int
ground::manhattandistance() {
    int sum = 0;
    for (int i = 0; i < N*N; i++) {
        std::pair<unsigned char, unsigned char> now = split(i);
        std::pair<unsigned char, unsigned char> proper = split((*ichiroku)[i]);
        sum += abs(now.first - proper.first) + abs(now.second - proper.second);
    }
    return sum;
}

void
ground::view() {
    for (int i = 0; i < N*N; i++) {
        if      (i % N == N-1)  printf("%3d\n", (*ichiroku)[i]);
        else                    printf("%3d ", (*ichiroku)[i]);
    }
    printf("spot: ichiroku[%d] = %d\n", this->spot, (*this->ichiroku)[this->spot]);
}

void
udlr::view() {
    printf("{ ");
    for (auto &i: this->directions) printf("%s ", UDLR_STR(i));
    // if (u) printf("u ");
    // if (d) printf("d ");
    // if (l) printf("l ");
    // if (r) printf("r ");
    printf("}\n");
}

void
ground::spotfinder() {
    int cost[N*N] = {__INT_MAX__};

    // temp saving.
    // !!! destructive(this->ichiroku) !!!
        unsigned char (*def16)[N*N] = this->ichiroku;

        unsigned char tmp16[N*N];
        this->ichiroku = &tmp16;
    //
    int i = 0;
    for (; i < N*N; i++) { // each "value of i" is a spot candidate.
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
    for (int i = 0; i < N*N; i++) {
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
    unsigned char v_to_i[N*N];
    for (int i = 0; i < N*N; i++) v_to_i[(*this->ichiroku)[i]] = i;

    for (int i = 0; i < N*N; i++) {
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
