// 该实现与裸实现相差不大，luogu上加上快读和printf时间98ms
#pragma once
#include "../base.h"

template<us LEN>
struct DSet {
    us far[LEN] = {0}, rnk[LEN] = {0};
    inl void init(us l, us r) { // WARN: INIT!!!
        for(; l<r; ++l) far[l] = l;
        mem(rnk+l, 0, r-l);
    }
    us find(us u) {
        if(far[u]==u) ret u;
        else ret far[u] = find(far[u]);
    }
    inl bool same(us l, us r) { ret find(l) == find(r); }
    // WARN: l'、r'会变为合并后的父、子节点
    inl bool merge(us &l, us &r) {
        if((l=find(l)) == (r=find(r))) ret 0;
        if(rnk[l]<rnk[r]) swap(l, r); // WARN: l',r'与l,r无一一对应关系
        rnk[l] += rnk[l] == rnk[r]; // 按高度度合并
        ret far[r]=l, 1;
    }
};