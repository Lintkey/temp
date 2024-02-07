// EI{us v, c; is w;} c为容量 w为费用
// CT: cost_type
// 原始费用必须是非负数
// 推荐使用pb_ds的堆
// 除非开O2否则不建议使用STL的
#pragma once
#include "../base.h"

template<us LEN, class CT=us>
struct PrimDual {
    bool vs[LEN];
    us s, t;
    CT ds[LEN], h[LEN];
    us rev[LEN];

    template<class G>
    void spfa(G &g) {
        mes(vs, g.n);
        fill(h, h+g.n, INF<CT>);
        queue<us> que; que.push(s);
        h[s] = 0; vs[s] = 1;
        typename G::E *ei;
        whi(!que.empty()) {
            us u = que.front(); que.pop(); vs[u] = 0;
            for(us e=g.head(u), v; ~e; g.next(e)) {
                ei = &g[e]; v = ei->v;
                if(ei->c&&h[v]>h[u]+ei->w) {
                    h[v] = h[u] + ei->w;
                    if(!vs[v]) que.push(v), vs[v]=1;
                }
            }
        }
    }

    template<class G>
    bool dij(G &g) {
        mes(vs, g.n);
        fill(ds, ds+g.n, INF<CT>);
        lque<pair<CT, us>> que;
        que.push({ds[s]=0, s});
        typename G::E *ei;
        whi(!que.empty()) {
            us u = que.top().second; que.pop();
            if(vs[u]) continue; vs[u] = 1;
            for(us e=g.head(u); ~e; g.next(e)) {
                ei = &g[e];
                us v = ei->v;
                CT d = h[u] + ei->w - h[v];
                if(ei->c&&ds[v]>ds[u]+d) {
                    ds[v] = ds[u] + d;
                    rev[v] = e ^ 1;
                    que.push({ds[v], v});
                }
            }
        }
        ret ds[t] != INF<CT>;
    }

    template<class FT=us, class G>
    tuple<CT, FT> mcmf(G &g, us _s, us _t) {
        s = _s; t = _t;
        CT cost=0;
        FT flow=0, f;
        spfa(g);
        whi(dij(g)) {
            f = INF<FT>;
            for(us u=0; u<g.n; ++u) h[u] += ds[u];
            for(us u=t; u!=s; u=g[rev[u]].v)
                tmn(f, FT(g[rev[u]^1].c));
            for(us u=t; u!=s; u=g[rev[u]].v) {
                g[rev[u]].c += f;
                g[rev[u]^1].c -= f;
            }
            flow += f;
            cost += f * h[t];
        }
        ret {cost, flow};
    }
};

// 特殊情况下Dinic的dfs常数大，EK反而比Dinic好
template<us LEN, class CT=us>
struct EK {
    us s, t, rev[LEN];
    CT ds[LEN];
    bool vs[LEN];

    template<class G>
    bool spfa(G &g) {
        fill(ds, ds+g.n, INF<CT>);
        queue<us> que; que.push(s);
        ds[s] = 0; vs[s] = 1;
        typename G::E *ei;
        whi(!que.empty()) {
            us u = que.front(); que.pop(); vs[u] = 0;
            for(us e=g.head(u), v; ~e; g.next(e)) {
                ei = &g[e]; v = ei->v;
                if(ei->c&&ds[v]>ds[u]+ei->w) {
                    ds[v] = ds[u] + ei->w;
                    rev[v] = e ^ 1;
                    if(!vs[v]) que.push(v), vs[v]=1;
                }
            }
        }
        ret ds[t] != INF<CT>;
    }

    template<class FT=us, class G>
    tuple<CT, FT> mcmf(G &g, us _s, us _t) {
        s = _s; t = _t;
        CT cost=0;
        FT flow=0, f;
        mes(vs, g.n);
        whi(spfa(g)) {
            f = INF<FT>;
            for(us u=t; u!=s; u=g[rev[u]].v)
                tmn(f, FT(g[rev[u]^1].c));
            for(us u=t; u!=s; u=g[rev[u]].v) {
                g[rev[u]].c += f;
                g[rev[u]^1].c -= f;
            }
            flow += f;
            cost += f * ds[t];
        }
        ret {cost, flow};
    }
};

template<us LEN, class CT=us>
struct Dinic {
    us hd[LEN], s, t;
    CT ds[LEN];
    bool vs[LEN];

    template<class G>
    bool spfa(G &g) {
        fill(ds, ds+g.n, INF<CT>);
        queue<us> que; que.push(s);
        ds[s] = 0; vs[s] = 1;
        typename G::E *ei;
        whi(!que.empty()) {
            us u = que.front(); que.pop(); vs[u] = 0;
            for(us e=g.head(u), v; ~e; g.next(e)) {
                ei = &g[e]; v = ei->v;
                if(ei->c&&ds[v]>ds[u]+ei->w) {
                    ds[v] = ds[u] + ei->w;
                    if(!vs[v]) que.push(v), vs[v]=1;
                }
            }
        }
        ret ds[t] != INF<CT>;
    }

    template<class FT, class G>
    FT fdfs(G &g, us u, FT lim) {
        if(u==t) ret lim;
        vs[u] = 1;
        typename G::E *ei;
        FT fct = lim, f;
        for(us v; ~hd[u]; g.next(hd[u])) {
            ei = &g[hd[u]]; v = ei->v;
            if(!vs[v]&&ei->c&&ds[u]+ei->w==ds[v]) {
                f = fdfs(g, v, min(fct, FT(ei->c)));
                ei->c -= f; g[hd[u]^1].c += f;
                if(!(fct-=f)) break;
            }
        }
        vs[u] = 0;
        ret lim - fct;
    }

    template<class FT=us, class G>
    tuple<CT, FT> mcmf(G &g, us _s, us _t) {
        s = _s; t = _t;
        CT cost=0;
        FT flow=0, f;
        mes(vs, g.n);
        whi(spfa(g)) {
            mec(g.hd, hd, g.n);
            whi((f=fdfs(g, s, INF<FT>))) {
                cost += f * ds[t];
                flow += f;
            }
        }
        ret {cost, flow};
    }
};