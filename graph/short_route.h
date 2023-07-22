// TIP: 以下实现比大多数裸实现常数要小
#pragma once
#include "../base.h"

// struct EI { v; w; }
template<class G, class D> // G=CFS<MAXN, MAXE, EI> 为了简略使用模板
void dij(G &g, us s, bool *vis, D *dis, D init=0) {
    mes(dis, g.n, 0x3f); mes(vis, g.n);
    using pdu = pair<D, us>;
    lque<pdu> que; que.push({dis[s] = init, s});
    D ds; typename G::E *ei;
    for(us u, v; !que.empty();) {
        u = que.top().second; que.pop();
        if(vis[u]) continue; vis[u]=1;
        for(us e = g.head(u); ~e; g.next(e))
            if(ei=&g[e], (ds=dis[u]+ei->w) < dis[v=ei->v])
                que.push({dis[v]=ds, v});
    }
}

// struct EI { v; w; }
template<class G, class D>
bool spfa(G &g, us s, bool *vis, us *cnt, D *dis, D init=0) {
    mes(dis, g.n, 0x3f); dis[s]=init;
    mes(cnt, g.n); mes(vis, g.n); vis[s]=1;
    queue<us> que; que.push(s);
    D ds; typename G::E *ei;
    for(us u, v; !que.empty();) {
        u=que.front(); que.pop(); vis[u]=0;
        for(us e=g.head(u); ~e; g.next(e))
            if(ei=&g[e], (ds=dis[u]+ei->w) < dis[v=ei->v])
                if(dis[v] = ds, !vis[v]) {
                    if(++cnt[v]>g.n) ret false;
                    que.push(v), vis[v]=1;
                }
    }
    ret true;
}