// 图的分量(component)：满足某种条件的极大子图
// 强连通分量scc：有向图，两点双向可达
// 边连通分量ecc：无向图，两点路径无必经边(割边)
// 点连通分量vcc：无向图，两点路径无必经点(割点)
// tarjan可以确认有向图中：
// 1. u是否能走到父节点：low[u]<dfn[u]
// 2. u到v的边是否为割边：low[v]>dfn[u]
// 在无向图中则能确认：
// 1. u是否能走到父节点：low[u]<dfn[u]
// 2. u与v的双向边是否为割边：low[v]>dfn[u]
// 3. u是否为v与f的割点：low[v]>=dfn[u]
// 如果是从虚拟节点tarjan，根节点确认是割点的条件改为
// 存在两棵及以上的子树，则根节点是这些子树间的割点
// scc：若u无法访问父节点，搜索栈余留在u后的节点构成scc
// ecc：若u与v的边是割边，搜索栈余留在v后的节点构成ecc
// vcc：若u为f与v间割点，搜索栈余留在v后的节点与u构成vcc
// 不同vcc可能存在交点
#include "../base.h"

template<class G>
struct scc{
    G &g;
    us *dn, *lw, ite;
    bool *vs;
    static vector<us> stk;
    scc(G &g, us *dfn, us *low, bool *vis):g(g) {
        dn = dfn; lw = low; vs = vis; ite = 0;
        for(us u=0; u<g.n; ++u)
            if(!dfn[u]) tarjan(u);
    }
    void tarjan(us u) {
        stk.push_back(u); vs[u] = 1;
        dn[u] = lw[u] = ++ite;
        for(us e=g.head(u), v; ~e; g.next(e)) {
            v = g[e].v;
            if(!dn[v]) { tarjan(v); tmn(lw[u], lw[v]); }
            else if(vs[v]) tmn(lw[u], dn[v]);
        }
        if(dn[u]==lw[u]) {
            for(us v=-1; v!=u;) {
                v = stk.back(); stk.pop_back();
                vs[v] = 0; lw[v] = dn[u];
            }
        }
    }
};

template<class G>
struct ecc{
    G &g;
    us *dn, *lw, ite;
    static vector<us> stk;
    ecc(G &g, us *dfn, us *low):g(g) {
        dn = dfn; lw = low; ite = 0;
        for(us u=0; u<g.n; ++u)
            if(!dfn[u]) tarjan(u);
    }
    void tarjan(us u, us f) {
        stk.push_back(u);
        dn[u] = lw[u] = ++ite;
        for(us e=g.head(u), v; ~e; g.next(e)) {
            v = g[e].v;
            if(!dn[v]) { tarjan(v, u); tmn(lw[u], lw[v]); }
            else if(v!=f) tmn(lw[u], dn[v]);
        }
        if(dn[u]==lw[u]) {
            for(us v=-1; v!=u;) {
                v = stk.back();
                stk.pop_back();
                lw[v] = dn[u];
            }
        }
    }
};

template<class G>
struct vcc{
    G &g;
    us *dn, *lw, ite;
    static vector<us> stk;
    vcc(G &g, us *dfn, us *low):g(g) {
        dn = dfn; lw = low; ite = 0;
        for(us u=0; u<g.n; ++u)
            if(!dfn[u]) tarjan(u, -1);
    }
    void tarjan(us u, us f) {
        stk.push_back(u);
        dn[u] = lw[u] = ++ite;
        for(us e=g.head(u), v; ~e; g.next(e)) {
            v = g[e].v;
            if(!dn[v]) {
                tarjan(v, u);
                tmn(lw[u], lw[v]);
                if(dn[u]<=lw[v]) {
                    // TODO:
                }
            } else if(v!=f) tmn(lw[u], dn[v]);
        }
    }
};