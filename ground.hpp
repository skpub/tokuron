#pragma once
#include <utility>
#include <cmath>
#include <set>
#include "constant.hpp"

#define UDLR_STR(v) (v) == 0 ? "u": (v) == 1 ? "d": (v) == 2 ? "l": "r"

enum udlr2 {
  u, d, l, r
};

struct udlr {
    std::set<udlr2> directions;
    void view();
};

struct ground {
    unsigned char (*ichiroku)[N*N];
    unsigned char spot = 0;
  public:
    unsigned long long sign();
    ground(unsigned char (&&)[N*N]);
    udlr move();
    void u();
    void d();
    void l();
    void r();
    void go(udlr2);
    int manhattandistance();
    void view();
  // private:
    void spotfinder();
    bool is_Even_DESTRUCTIVE();
};
