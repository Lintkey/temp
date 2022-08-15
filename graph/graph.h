#pragma once
#include "../base.h"

template<us MAXN, us MAXE, class EI>
struct CFS {  // 链式前向星
    using E = EI;
    us n, hd[MAXN], nx[MAXE], it; EI val[MAXE];
    inl void init(us _n) { mem(hd, it=-1, n=_n); }
    inl void add(us u, EI ei) {
        nx[++it] = hd[u]; val[it]=ei; hd[u]=it;
    }
    inl us head(con us u) con { ret hd[u]; }
    inl void next(us &e) con { e=nx[e]; }
    EI &operator[](con us e) { ret val[e]; }
};

// template<class EI>
// struct CFSBase {
//     virtual void init(us _n) = 0;
//     virtual void add(us u, EI ei) = 0;
//     virtual us head(con us u) con = 0;
//     virtual void next(us &e) con = 0;
//     virtual EI &operator[](con us e) = 0;
// };