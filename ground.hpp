#pragma once
#include <utility>
#include <cmath>
#include <set>

#define UDLR_STR(v) (v) == 0 ? "u": (v) == 1 ? "d": (v) == 2 ? "l": "r"

enum udlr2 {
  u, d, l, r
};

struct udlr {
    std::set<udlr2> directions;
    void view();
};

struct ground {
    unsigned char (*ichiroku)[16];
    unsigned char spot = 0;
  public:
    unsigned long long sign();
    ground(unsigned char (&&)[16]);
    udlr move();
    void u();
    void d();
    void l();
    void r();
    int manhattandistance();
    void view();
  // private:
    void spotfinder();
    bool is_Even_DESTRUCTIVE();
};
