#include "random.hxx"
#include <random>

namespace Essentials::Math
{
    int randNum(int start, int end) {
        static std::random_device rd;
        static std::mt19937 mt{rd()};
        std::uniform_int_distribution<int> dist{start, end};
        return dist(mt);
    }
}
