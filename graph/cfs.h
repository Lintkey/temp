#pragma once
#include "../base.h"

#define GFOR(g, u) for(us e=g.head(u); ~e; g.next(e))

template<us NLEN, us ELEN=NLEN*2, class EI=us>
struct CFS {  // 链式前向星
    using E = EI; // 此声明用于辅助其他算法的封装
    us n, hd[NLEN], nx[ELEN], it; EI val[ELEN];
    void init(us _n) { mes(hd, n=_n, it=-1); } // WARN: INIT!!!
    void add(us u, con EI &ei) {
        nx[++it] = hd[u]; val[it]=ei; hd[u]=it; }
    us head(con us u) con { ret hd[u]; }
    void next(us &e) con { e=nx[e]; }
    EI &operator[](con us e) { ret val[e]; }
};