#include "../base.h"

struct custom_hash {
    static ul split(ul x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(ul x) con {
        static con ul FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return split(x + FIXED_RANDOM);
    }
};