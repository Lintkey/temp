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

template<us NLEN, us ELEN=NLEN*2, class EI=us>
struct STG {
    using E = EI; // 此声明用于辅助其他算法的封装
    us n, hd[NLEN], ed[NLEN], it;
    vector<pair<us, EI>> pool;
    void init(us _n) { n = _n; pool.clear(); } // WARN: INIT!!!
    void add(us u, EI ei) { pool.push_back({u, ei}); }
    void build() {
        let sz = pool.size();
        sort(pool.begin(), pool.end(),
            [](let &l, let &r){ ret l.first<r.first; });
        for(us i=0; i<n; ++i) {
            hd[i] = it;
            whi(it<sz&&pool[it].first==i) ++it;
            ed[i] = it;
        }
    }
    us head(con us u) con { ret hd[u]; }
    us end(con us u) con { ret ed[u]; }
    EI &operator[](con us e) { ret pool[e].second; }
};