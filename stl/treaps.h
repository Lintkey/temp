// 类set，可查询
#pragma once
#include "../base.h"
#include "pool_ite.h"

template<us LEN, class T, us NUM = 1>
struct Treaps {
    static cer us SZ = LEN + 1;
    us rt[NUM], ln[SZ], rn[SZ];
    pit<1> ite;
    us sz[SZ], ct[SZ], lev[SZ];
    T val[SZ];
    Treaps(us N=1) { ln[0] = rn[0] = 0; init(N); }
    void init(us N=1) { ite.init(); mes(rt, N); }
    void up_siz(us u) { sz[u] = sz[ln[u]] + sz[rn[u]] + ct[u]; }
    void rot_left(us &u) {
        us f = rn[u]; rn[u] = ln[f]; ln[f] = u;
        sz[f] = sz[u]; up_siz(u); u = f;
    }
    void rot_right(us &u) {
        us f = ln[u]; ln[u] = rn[f]; rn[f] = u;
        sz[f] = sz[u]; up_siz(u); u = f;
    }

    us add(us &u, con T &v) {
        if(u) {
            ++sz[u];
            if(val[u]==v) ++ct[u];
            else if(val[u]>v) { if(add(ln[u], v)<lev[u]) rot_right(u); }
            else if(add(rn[u], v)<lev[u]) rot_left(u);
        } else {
            u = ++ite; ln[u] = rn[u] = 0;
            sz[u] = ct[u] = 1; lev[u] = rand();
            val[u] = v;
        } ret lev[u];
    }

    // all指定是否删除全部元素
    void rm(us &u, con T &v, bool all=false) {
        static us _del;
        if(u) {
            if(val[u]==v) {
                _del = all?ct[u]:1;
                if(ct[u]>_del) sz[u] -= _del, ct[u] -= _del;
                else {
                    if(ln[u]&&rn[u]) {
                        if(lev[ln[u]]>lev[rn[u]]) rot_left(u), rm(u, v, all);
                        else rot_right(u), rm(u, v, all);
                    } else ite.gc(u), u = ln[u] + rn[u];
                }
            } else {
                if(val[u]<v) rm(rn[u], v);
                else rm(ln[u], v);
                sz[u] -= _del;
            }
        } else _del = 0;
    }

    us get_rank(us u, con T &v) {
        us res = 0;
        whi(u) {
            if(val[u]>v) u = ln[u];
            else if(val[u]==v) ret res + sz[ln[u]];
            else { res += sz[ln[u]] + ct[u]; u = rn[u]; }
        } ret res;
    }

    con T& rank_find(us u, us k) {
        assert(k<sz[u]);
        whi(u) {
            if(k<sz[ln[u]]) u = ln[u];
            else if(k>=sz[ln[u]]+ct[u]) {
                k -= sz[ln[u]] + ct[u]; u = rn[u];
            } else ret val[u];
        } exit(1);
    }

    // 获取第一个(>v的)值的位置，若v>=所有值返回ite+1
    // WARN: 不能用于修改和查询区间数量
    // 区间数量查询请用get_rank(r)-get_rank(l)
    us upper(us u, con T &v) {
        us res = end();
        whi(u) {
            if(val[u]<=v) u = rn[u];
            else { res = u; u = ln[u]; }
        } ret res;
    }

    // 获取第一个(>=v的)值的位置，若v>所有值返回ite+1
    // WARN: 不能用于修改和查询区间数量
    // 区间数量查询请用get_rank(r)-get_rank(l)
    us lower(us u, con T &v) {
        us res = end();
        whi(u) {
            if(val[u]<v) u = rn[u];
            else if(v<val[u]) { res = u; u = ln[u]; }
            else ret u;
        } ret res;
    }

    us end() { ret ite.end(); }

    struct Treap {
        Treaps &pool;
        us &rot;

        us end() { ret pool.end(); }
        us size() { ret pool.sz[rot]; }
        us add(con T &v) { ret pool.add(rot, v); }
        void rm(con T &v, bool all=false) { pool.rm(rot, v, all); }
        us get_rank(con T &v) { ret pool.get_rank(rot, v); }
        con T& rank_find(us k) { ret pool.rank_find(rot, k); }
        con T& operator[](us k) { ret rank_find(k); }
        us upper(con T &v) { ret pool.upper(rot, v); }
        us lower(con T &v) { ret pool.lower(rot, v); }
    };

    Treap operator[](us k) { ret Treap{*this, rt[k]}; }
};