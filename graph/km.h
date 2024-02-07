#pragma once
#include "../base.h"

// 最大权匹配，完美匹配需修改add_edge和init
template<us LEN, class T = us>
struct KM {
    us n, lmat[LEN], rmat[LEN];
    T g[LEN][LEN], lstd[LEN], rstd[LEN], dis[LEN];
    us adp[LEN]; // 右节点增广匹配
    bool lvis[LEN], rvis[LEN];

    queue<us> que;

    template<class WT>
    void add_edge(us u, us v, WT w) {
        g[u][v] = max(WT(0), w);
    }

    bool try_adapt(us v) {  // 回溯增广匹配
        rvis[v] = 1;
        if(~rmat[v]) {  // 没法匹配
            que.push(rmat[v]);
            lvis[rmat[v]] = 1;
            ret 0;
        }
        whi(~v) // 一直增广匹配直至adapt[v]未匹配
            swap(v, lmat[rmat[v]=adp[v]]);
        ret 1;
    }

    void bfs(us u) {
        fill(dis, dis+n, INF<T>);
        mes(lvis, n);
        mes(rvis, n);

        queue<us> q;
        swap(que, q);
        que.push(u);
        lvis[u] = 1;
        for(;;) {
            whi(!que.empty()) {
                u = que.front(); que.pop();
                for(us v=0; v<n; ++v) {
                    if(!rvis[v]) {
                        T ds = lstd[u]+rstd[v]-g[u][v];
                        if(dis[v]>=ds) {
                            adp[v] = u;
                            if(ds) dis[v] = ds;
                            else if(try_adapt(v)) ret;
                        }
                    }
                }
            }
            T df = INF<T>;
            for(us v=0; v<n; ++v)
                if(!rvis[v]) tmn(df, dis[v]);
            for(us i=0; i<n; ++i) {
                if(lvis[i]) lstd[i] -= df;
                if(rvis[i]) rstd[i] += df;
                else dis[i] -= df;
            }
            for(us v=0; v<n; ++v)
                if(!rvis[v]&&!dis[v]&&try_adapt(v))
                    ret;
        }
    }

    void init(us _n) {
        n = _n;
        for(us i=0; i<n; ++i)
            mes(g[i], n);
    }

    void match() {
        mes(lstd, n);
        mes(rstd, n);
        mes(lmat, n, -1);
        mes(rmat, n, -1);
        for(us u=0; u<n; ++u)
            for(us v=0; v<n; ++v)
                tmx(lstd[u], T(g[u][v]));
        
        for(us u=0; u<n; ++u) bfs(u);
    }
};