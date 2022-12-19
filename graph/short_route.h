// TIP: 以下实现比大多数裸实现常数要小
#pragma once
#include "../base.h"

// struct EI { v; w; }
template<class G, class D> // G=CFS<MAXN, MAXE, EI> 为了简略使用模板
inl void dij(G &g, us s, bool *vis, D *dis) {
    mem(dis, g.n, 0xff);
    mem(vis, g.n);
    using pdu = pair<D, us>;
    priority_queue<pdu, vector<pdu>, greater<pdu>> que;
    que.push({dis[s] = 0, s}); D ds; typename G::E *ei;
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
inl void spfa(G &g, us s, bool *vis, D *dis) {
    mem(dis, g.n, 0xff); dis[s]=0;
    mem(vis, g.n); vis[s]=1;
    queue<us> que; que.push(s);
    D ds; typename G::E *ei;
    for(us u, v; !que.empty();) {
        u=que.front(); que.pop(); vis[u]=0;
        for(us e=g.head(u); ~e; g.next(e))
            if(ei=&g[e], (ds=dis[u]+ei->w) < dis[v=ei->v])
                if(dis[v] = ds, !vis[v]) que.push(v), vis[v]=1;
    }
}