#pragma once
#include <utility>
#include <cmath>

struct udlr {
    bool u, d, l, r;
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
