// 基本没用
#pragma once
#include "../base.h"

template<us LEN, class T>
struct Arr {
    T pool[LEN];
    operator T*() { ret pool; }
    void init(con T x, us n=LEN) { fill(pool, pool+n, x); }
};