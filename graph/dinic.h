#pragma once
#include "../base.h"

template<class G>
inl void cbfs(G &g, us s, us *dis) {
    mem(dis, 0xff, g.n); dis[s] = 0;
    queue<us> que; que.push(s);
    typename G::E *ei;
    for(us u, v, ds; !que.empty();) {
        u=que.front(); que.pop(); ds=dis[u]+1;
        for(us e=g.head(u); ~e; g.next(e))
            if(ei=&g[e], ei->c&&(dis[v=ei->v] == -1))
                que.push(v), dis[v]=ds;
    }
}

us *fdfs_hd, *fdfs_ds, fdfs_t;
template<class G>
typename G::E::FT fdfs(G &g, us u, typename G::E::FT f) {
    if(u==fdfs_t) ret f; typename G::E *ei;
    using FT = typename G::E::FT; FT fct = f;
    for(us v, c; ~fdfs_hd[u]; g.next(fdfs_hd[u]))
        if(ei=&g[fdfs_hd[u]], (ei->c)&&(fdfs_ds[u]+1 == fdfs_ds[v=ei->v])) {
            c = fdfs(g, v, min(fct, FT(ei->c)));
            ei->c -= c; g[fdfs_hd[u]^1].c += c;
            if(!(fct-=c)) break; // 配合当前弧优化
        }
    ret f - fct;
}

// TODO: ISAP，未优化时复杂度和dinic相同，优化后可大幅提升速度
// 最坏复杂度O((n^2)*m)，二分匹配问题O(m*sqrt(n))
// hd, ds: 缓存数组，传入两个大小与g.n(节点数)等大的无用数组即可
template<class G>
inl typename G::E::FT dinic(G &g, us s, us t, us *hd, us *ds) {
    fdfs_hd = hd; fdfs_ds = ds; fdfs_t = t;
    typename G::E::FT res=0;
    whi(cbfs(g, s, ds), ~ds[t]) {
        memcpy(hd, g.hd, g.n * sf(us));
        res += fdfs(g, s, G::E::FINF);
    } ret res;
}

// TODO: MPM O(n^3)