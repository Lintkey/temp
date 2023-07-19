#pragma once
#include "../base.h"

// 二类应用：静态区间查询范围内k小值
// 单个树记录数值范围内数的个数
// 对区间[0, 0..=n)建树([0, 0)build, [0, 1..=n)insert)
// kque比对[0, lid)树和[0, rid)树的信息，找到树区间[lid, rid)第k小x(insert(x))
// 注意id是0..=n，因此查询树区间[l, r)第k小x，应调用kque(l, r, 0, size, k):
template<us LEN, us PLEN>
struct PSegTree {
    struct Node {
        us su, lb, rb;
        Node *ln, *rn;
    } pool[PLEN], *rt[LEN], *ite;
    us sz;
    void init(us l, us r) {
        ite = pool - 1;
        build(l, r);
        rt[sz=0] = ite;
    }
    // 以...为蓝本创建新历史
    void insert(us sid, us x)
        { insert(rt[sid], x); rt[++sz] = ite; }
    // 查询树区间[lid, rid)第k小x
    us kque(us lid, us rid, us k)
        { ret kque(rt[lid], rt[rid], k); }
    // 查询树区间[lid, rid)在区间[l,r)上的差值
    us que(us lid, us rid, us l, us r)
        { ret que(rt[lid], rt[rid], l, r); }
    void insert(Node *cur, us x) {
        if(cur->ln != nullptr) {
            var ln = cur->ln, rn = cur->rn;
            if(ln->rb > x) insert(ln, x), ln = ite;
            else insert(rn, x), rn = ite;
            *++ite = { cur->su+1, cur->lb, cur->rb, ln, rn };
        } el *++ite = *cur, ++ite->su;
    }
private:
    void build(us l, us r) {
        Node *ln = nullptr, *rn = nullptr;
        if(l+1 != r) {
            con us MID = (l + r) >> 1;
            build(l, MID); ln = ite;
            build(MID, r); rn = ite;
        }
        *++ite = { 0, l, r, ln, rn };
    }
    us kque(Node *ln, Node *rn, us k) {
        if(ln->ln != nullptr) {
            con us MID = ln->ln->rb, su = rn->ln->su - ln->ln->su;
            if(su >= k) ret kque(ln->ln, rn->ln, k);
            else ret kque(ln->rn, rn->rn, k - su);
        } ret ln->lb;
    }
    us que(Node *ln, Node *rn, us l, us r) {
        if(ln->lb<=l && r<=ln->rb) ret rn->su - ln->su;
        el {
            con us MID = ln->ln->rb; us res = 0;
            if(l<MID) res += que(ln->ln, rn->ln, l, min(MID, r));
            if(r>MID) res += que(ln->rn, rn->rn, max(l, MID), r);
            ret res;
        }
    }
};