// TIP: 以下实现比大多数裸实现常数要小
#pragma once
#include "../base.h"

// struct EI { v; w; }
template<class G, class D> // G=CFS<MAXN, MAXE, EI> 为了简略使用模板
inl void dij(G &g, us s, bool *vis, D *dis, D init=0) {
    mem(dis, g.n, 0x3f); mem(vis, g.n);
    using pdu = pair<D, us>;
    priority_queue<pdu, vector<pdu>, greater<pdu>> que;
    que.push({dis[s] = init, s}); D ds; typename G::E *ei;
    for(us u, v; !que.empty();) {
        u = que.top().second; que.pop();
        if(vis[u]) continue; vis[u]=1;
        for(us e = g.head(u); ~e; g.next(e))
            if(ei=&g[e], (ds=dis[u]+ei->w) < dis[v=ei->v])
                que.push({dis[v]=ds, v});
    }
}

// 备用，随机数据下良好，但是会被菊花图卡
// struct EI { v; w; }
template<class G, class D>
inl bool spfa(G &g, us s, bool *vis, us *cnt, D *dis, D init=0) {
    mem(dis, g.n, 0x3f); dis[s]=init;
    mem(cnt, g.n); mem(vis, g.n); vis[s]=1;
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