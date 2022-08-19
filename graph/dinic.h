// 最坏复杂度O((n^2)*m)，二分匹配问题O(m*sqrt(n))
// 使用示例 https://www.luogu.com.cn/record/84394094
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
template<class T, class G>
T fdfs(G &g, us u, T f) {
    if(u==fdfs_t) ret f; typename G::E *ei; T fct = f;
    for(us v, c; ~fdfs_hd[u]; g.next(fdfs_hd[u]))
        if(ei=&g[fdfs_hd[u]], (ei->c)&&(fdfs_ds[u]+1 == fdfs_ds[v=ei->v])) {
            c = fdfs(g, v, min(fct, T(ei->c)));
            ei->c -= c; g[fdfs_hd[u]^1].c += c;
            if(!(fct-=c)) break; // 配合当前弧优化
        }
    ret f - fct;
}

// 使用需要指定预期返回类型, 例如：dinic<ul>(...)
// hd, ds: 缓存数组，传入两个大小与g.n(节点数)等大的无用数组即可(也可用于分析调试)
// struct EI { v; c; }
template<class T, class G>
inl T dinic(G &g, us s, us t, us *hd, us *ds) {
    fdfs_hd = hd; fdfs_ds = ds; fdfs_t = t; T res=0;
    whi(cbfs(g, s, ds), ~ds[t]) {
        memcpy(hd, g.hd, g.n * sf(us));
        res += fdfs(g, s, INF<T>());
    } ret res;
}

// 加双向边 (u->v, c) (v->u, 0)
template<class G, class EI>
inl void add_ce(G &g, us u, EI ei) {
    g.add(u, ei); swap(u, ei.v); // 高版本有move优化，不必^
    ei.c = 0; g.add(u, ei);
}