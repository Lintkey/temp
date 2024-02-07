#pragma once
#include "../base.h"

template<class T, us LEN=32>
struct LBasis {
    T pool[LEN], sz;
    void init() { mes(pool, LEN, sz=0); }
    void insert(T v) {
        for(us i=LEN; ~--i;)
            if((v>>i)&1) {
                if(pool[i]) v ^= pool[i];
                else { pool[i] = v; ++sz; ret; }
            }
    }
    T max() {
        T res = 0;
        for(us i=LEN; ~--i;)
            if(!((res>>i)&1)) res ^= pool[i];
        ret res;
    }
    bool can_merge(T v) {
        for(us i=LEN; v&&~--i;)
            if((v>>i)&1) {
                if(pool[i]) v ^= pool[i];
                else ret false;
            }
        ret true;
    }
};