// 经爆改分离后，常数已控制在合理范围内(个人测试均比手敲速度快或差不多)
#pragma once
#include "../base.h"

// 可维护[0, LEN)范围，所有[l, r)均左闭右开
// 调用节点成员使用->访问，例：seg->add(l, r, 1);
// 嫌麻烦可以直接裸用下面的Node
template<us LEN, class Node>
struct SegTree {
    Node pool[(LEN << 1) - 1], *iter = pool;
    inl Node *operator->() { ret pool; }
    inl void init(us l, us r) { pool->build(&(iter=pool), l, r); }
};

template<class Node>
struct BSNode {
    us lb, rb;
    Node *ln, *rn;
    void init(Node **ite, us l, us r) { // TODO: 待优化，传参比较奇怪
        if((lb=l) + 1 != (rb=r)) {
            con us MID = (l + r) >> 1;
            (ln = ++*ite)->build(ite, l, MID);
            (rn = ++*ite)->build(ite, MID, r);
        } else ln = rn = nullptr;
    }
};

// BNode 基础Node，区间乘/加/查询
template<class T>
struct BNode: public BSNode<BNode<T>> {
    using F = BSNode<BNode<T>>;
    T val, mu, ad;

    void build(BNode **ite, us l, us r) {
        val = ad = 0; mu = 1;
        ret F::init(ite, l, r);
    }
    inl void push() {
        if(mu ^ 1) { F::ln->mt(mu); F::rn->mt(mu); mu = 1; }
        if(ad) { F::ln->at(ad); F::rn->at(ad); ad = 0; }
    }
    T que(us l, us r) {
        if(l == F::lb && F::rb == r) ret val;
        else {
            con us md = F::ln->rb; push(); T res = 0;
            if(l < md) res += F::ln->que(l, min(md, r));
            if(r > md) res += F::rn->que(max(l, md), r);
            ret res;
        }
    }

    inl void at(T up) { ad += up; val += up * T(F::rb - F::lb); }
    void add(us l, us r, T up) {
        if(l == F::lb && F::rb == r) at(up);
        else {
            con us md = F::ln->rb; push();
            if(l < md) F::ln->add(l, min(md, r), up);
            if(r > md) F::rn->add(max(l, md), r, up);
            val = F::ln->val + F::rn->val;
        }
    }
    inl void mt(T up) { mu *= up; ad *= up; val *= up; }
    void mul(us l, us r, T up) {
        if(l == F::lb && F::rb == r) mt(up);
        else {
            con us md = F::ln->rb; push();
            if(l < md) F::ln->mul(l, min(md, r), up);
            if(r > md) F::rn->mul(max(l, md), r, up);
            val = F::ln->val + F::rn->val;
        }
    }
};

// MNode 极值Node，使用类似BNode，less取最小值，greater取最大值
// 区间乘不考虑负数！！！建议开两个模拟
template<class T, T DEF, class cmp = less<T>>
struct MNode: public BSNode<MNode<T, DEF, cmp>> {
    using F = BSNode<MNode<T, DEF, cmp>>;
    T val, mu, ad;

    void build(MNode **ite, us l, us r) {
        ad = 0; mu = 1; val = DEF;
        ret F::init(ite, l, r);
    }
    inl void push() {
        if(mu ^ 1) { F::ln->mt(mu); F::rn->mt(mu); mu = 1; }
        if(ad) { F::ln->at(ad); F::rn->at(ad); ad = 0; }
    }
    T que(us l, us r) {
        if(l == F::lb && F::rb == r) ret val;
        else {
            con us md = F::ln->rb; push();
            con bool lhs = l < md, rhs = r > md;
            if(lhs ^ rhs)
                ret lhs ? F::ln->que(l, min(md, r))
                        : F::rn->que(max(l, md), r);
            con T lv = F::ln->que(l, min(md, r));
            con T rv = F::rn->que(max(l, md), r);
            ret cmp()(lv, rv) ? lv : rv;
        }
    }

    inl void at(T up) { ad += up; val += up; }
    void add(us l, us r, T up) {
        if(l == F::lb && F::rb == r) at(up);
        else {
            con us md = F::ln->rb; push();
            if(l < md) F::ln->add(l, min(md, r), up);
            if(r > md) F::rn->add(max(l, md), r, up);
            val = cmp()(F::ln->val, F::rn->val) ? F::ln->val : F::rn->val;
        }
    }
    inl void mt(T up) { mu *= up; ad *= up; val *= up; }
    void mul(us l, us r, T up) {
        if(l == F::lb && F::rb == r) mt(up);
        else {
            con us md = F::ln->rb; push();
            if(l < md) F::ln->mul(l, min(md, r), up);
            if(r > md) F::rn->mul(max(l, md), r, up);
            val = cmp()(F::ln->val, F::rn->val) ? F::ln->val : F::rn->val;
        }
    }
};