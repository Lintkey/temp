#pragma once
#include "../base.h"

#define ST_FOR               \
    for(us i = 1; i <= logl; ++i) \
        for(us j = l; j < r; ++j) 

template<us LEN, us LOG_L>
struct STF {
    us far[LOG_L + 1][LEN];
    con us *operator[](us idx) con { ret far[idx]; }
    void init(us l, us r, us logl = LOG_L) { // WARN: INIT!!!
        iota(far[0] + l, far[0] + r - 1, l + 1);
        far[0][r - 1] = r - 1;
        ST_FOR far[i][j] = far[i - 1][far[i - 1][j]];
    }
};

template<us LEN, us LOG_L, class T, class cmp = less<con T &>>
struct ST {
    con STF<LEN, LOG_L> &far;
    T val[LOG_L + 1][LEN];
    ST(STF<LEN, LOG_L> &_f) : far(_f) {}
    operator T*() { ret far[0]; } // 供memset使用
    T *operator()() { ret val[0]; } // 供scanf使用
    T &operator[](us idx) { ret val[0][idx]; } // 供cin,fin使用
    con T &que(us l, us r) {
        con us logd = log2(r - l); // TODO: 优化
        con T &lv = val[logd][l], &rv = val[logd][r - (1 << logd)];
        ret cmp()(lv, rv) ? lv : rv;
    }
    void init(us l, us r, us logl = LOG_L) { ST_FOR { // WARN: INIT!!!
        con T &lv = val[i - 1][j], &rv = val[i - 1][far[i - 1][j]];
        val[i][j] = cmp()(lv, rv) ? lv : rv;
    }}
};
#undef ST_FOR
