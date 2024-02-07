#pragma once
#include "../base.h"

// struct EI { v; }
// 注意，rot高32位存第二重心(如有)
namespace grav_data {
    us num, *sz, *mx;
    bool *vis;
    ul rot;

    void set(us n=0) { rot=-1, num=n; }

    void init(us *sz_, us *mx_, bool *vis_=nullptr) {
        sz = sz_; mx = mx_; vis = vis_; rot = -1;
    }

    template<class G>
    void grav(G &g, us u, us f=-1) {
        sz[u] = 1; mx[u] = 0;
        for(us e=g.head(u), v; ~e; g.next(e))
            if((v=g[e].v)!=f) {
                grav(g, v, u);
                tmx(mx[u], sz[v]);
                sz[u] += sz[v];
            }
        tmx(mx[u], g.n-sz[u]);
        if(!(~rot)||mx[u]<mx[us(rot)]) rot = (ul(-1)<<32) | u;
        else if(mx[u]==mx[us(rot)]) rot = (rot<<32) | u;
    }

    // 子树重心，重心分解用
    template<class G>
    void sub_grav(G &g, us u, us f=-1) {
        sz[u] = 1; mx[u] = 0;
        for(us e=g.head(u), v; ~e; g.next(e))
            if((v=g[e].v)!=f&&!vis[v]) {
                sub_grav(g, v, u);
                tmx(mx[u], sz[v]);
                sz[u] += sz[v];
            }
        tmx(mx[u], num-sz[u]);
        if(!(~rot)||mx[u]<mx[us(rot)]) rot = (ul(-1)<<32) | u;
        else if(mx[u]==mx[us(rot)]) rot = (rot<<32) | u;
    }
}

using grav_data::init;
using grav_data::grav;
using grav_data::set;
using grav_data::sub_grav;