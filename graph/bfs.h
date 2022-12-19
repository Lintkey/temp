// WARN: 此实现未经测试
#pragma once
#include "../base.h"

// struct EI { v; }
template<class G, class D>
inl void bfs(G &g, us s, D *dis) {
    mem(dis, g.n, 0xff); dis[s] = 0;
    queue<D> que; que.push(s);
    D ds; typename G::E *ei;
    for(us u, v; !que.empty();) {
        u=que.front(); que.pop(); ds=dis[u]+1;
        for(us e=g.head(u); ~e; g.next(e))
            if(ei=&g[e], dis[v=ei->v] == -1)
                que.push(v), dis[v]=ds;
    }
}