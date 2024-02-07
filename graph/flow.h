// 最坏复杂度O((n^2)*m)，二分匹配问题O(m*sqrt(n))
// EI {v, c};
#pragma once
#include "../base.h"

template<us LEN>
struct ISAP {
    bool done;
    us hd[LEN], ds[LEN], ct[LEN+1], s, t;

    template<class G>
    void cbfs(G &g) {
        mes(ct, g.n);
        mes(ds, g.n, -1);
        ds[t] = 0; ct[0] = 1;
        queue<us> que; que.push(t);
        typename G::E *ei;
        for(us u, v; !que.empty();) {
            u = que.front(); que.pop();
            for(us e=g.head(u); ~e; g.next(e)) {
                ei = &g[e]; v = ei->v;
                if(~ds[v]) continue;
                ++ct[ds[v]=ds[u]+1];
                que.push(v);
            }
        }
    }

    template<class T, class G>
    T fdfs(G &g, us u, T f) {
        if(u==t) ret f;
        typename G::E *ei; T fct = f;
        for(us v, c; ~hd[u]; g.next(hd[u])) {
            ei = &g[hd[u]]; v = ei->v;
            if(ei->c&&ds[u]==ds[v]+1) {
                c = fdfs(g, v, min(fct, T(ei->c)));
                ei->c -= c; g[hd[u]^1].c += c;
                if(!(fct-=c)) ret f;
            }
        }
        done |= !--ct[ds[u]];
        ++ct[++ds[u]];
        ret f - fct;
    }

    template<class FT=us, class G>
    FT flow(G &g, us _s, us _t) {
        s = _s; t = _t; FT res = 0;
        cbfs(g); done = !~ds[s];
        whi(!done) {
            mec(g.hd, hd, g.n);
            res += fdfs(g, s, FT(-1));
        } ret res;
    }
};

template<us LEN>
struct Dinic {
    us hd[LEN], ds[LEN], s, t;

    template<class G>
    void cbfs(G &g) {
        mes(ds, g.n, -1); ds[s] = 0;
        queue<us> que; que.push(s);
        typename G::E *ei;
        for(us u, v; !que.empty();) {
            u=que.front(); que.pop();
            for(us e=g.head(u); ~e; g.next(e)) {
                ei = &g[e]; v = ei->v;
                if(ei->c&&!~ds[v])
                    que.push(v), ds[v]=ds[u]+1;
            }
        }
    }

    template<class T, class G>
    T fdfs(G &g, us u, T f) {
        if(u==t) ret f;
        typename G::E *ei; T fct = f;
        for(us v, c; ~hd[u]; g.next(hd[u])) {
            ei = &g[hd[u]]; v = ei->v;
            if(ei->c&&ds[u]+1==ds[v]) {
                c = fdfs(g, v, min(fct, T(ei->c)));
                ei->c -= c; g[hd[u]^1].c += c;
                if(!(fct-=c)) ret f;
            }
        }
        ret f - fct;
    }

    template<class FT=us, class G>
    FT flow(G &g, us _s, us _t) {
        s = _s; t = _t; FT res=0;
        whi(cbfs(g), ~ds[t]) {
            mec(g.hd, hd, g.n);
            res += fdfs(g, s, FT(-1));
        }
        ret res;
    }
};