// 为了解耦和减小码量，这里的图仅用来储存边的信息
// 欲存储诸如距离(dis)，是否访问(vis)等信息，建议自己开辟数组或结构体封装，这样更好
// 旧使用示例: https://www.luogu.com.cn/record/83557916
#pragma once
#include "../base.h"

// WARN: ELEN没有开双倍空间
template<us NLEN, us ELEN, class EI>
struct CFS {  // 链式前向星
    using E = EI; // 此声明用于辅助其他算法的封装
    us n, hd[NLEN], nx[ELEN], it; EI val[ELEN];
    inl void init(us _n) { mem(hd, n=_n, it=-1); } // WARN: INIT!!!
    inl void add(us u, con EI &ei) {
        nx[++it] = hd[u]; val[it]=ei; hd[u]=it; }
    inl us head(con us u) con { ret hd[u]; }
    inl void next(us &e) con { e=nx[e]; }
    inl EI &operator[](con us e) { ret val[e]; }
};

// template<class EI>
// struct CFSBase {
//     virtual void init(us _n) = 0;
//     virtual void add(us u, EI ei) = 0;
//     virtual us head(con us u) con = 0;
//     virtual void next(us &e) con = 0;
//     virtual EI &operator[](con us e) = 0;
// };