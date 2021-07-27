#include "constant.hpp"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

struct heap {
    unsigned char ground[N*N];
    int cost;
    int moves;
    heap *parent;
};

class Game {
    vector<heap> dp_table;
    unordered_map<long long, int> sign_to_ground;
  public:
    Game(ground);
};
