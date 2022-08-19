// TIP: 以下实现比大多数裸实现常数要小
// LOG_L不用开到(1<<LOG_L)>=LEN，只用开到(1<<(LOG_L+1))>LEN，即LEN的bit位数
// 注意，老版本编译器可能没有iota、log2，请手动更改17~18和33~34行
// WARN: 使用前请记得stf.init(l, r)和st.init(l, r)
#pragma once
#include "../base.h"

#define ST_FOR               \
    for(us i = 1; i <= logl; ++i) \
        for(us j = l; j < r; ++j) 

template<us LEN, us LOG_L>
struct STF {
    us far[LOG_L + 1][LEN] = {0};
    inl con us *operator[](us idx) con { ret far[idx]; }
    inl void init(us l, us r, us logl = LOG_L) { // WARN: INIT!!!
        iota(far[0] + l, far[0] + r - 1, l + 1);
        // for(us i=l+1; i<r; ++i) far[0][i - 1] = i; // 备用(老版本没有iota)
        far[0][r - 1] = r - 1;
        ST_FOR far[i][j] = far[i - 1][far[i - 1][j]];
    }
};

template<us LEN, us LOG_L, class T, class cmp = less<con T &>>
struct ST {
    con STF<LEN, LOG_L> &far;
    T val[LOG_L][LEN];
    ST(STF<LEN, LOG_L> &_f) : far(_f) {}
    inl operator T*() { ret far[0]; } // 供memset使用
    inl T *operator()() { ret val[0]; } // 供scanf使用
    inl T &operator[](us idx) { ret val[0][idx]; } // 供cin,fin使用
    inl con T &que(us l, us r) {
        con us logd = log2(r - l); // TODO: 优化
        // us logd = log(r - l) / log(2); // 备用(老版本不支持log2)
        con T &lv = val[logd][l], &rv = val[logd][r - (1 << logd)];
        ret cmp()(lv, rv) ? lv : rv;
    }
    inl void init(us l, us r, us logl = LOG_L) { ST_FOR { // WARN: INIT!!!
        con T &lv = val[i - 1][j], &rv = val[i - 1][far[i - 1][j]];
        val[i][j] = cmp()(lv, rv) ? lv : rv;
    }}
};
#undef ST_FOR
