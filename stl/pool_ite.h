#pragma once
#include "../base.h"

// 对反复开辟删除碎片空间可采用此做法
template<us S=0>
struct pit {
    Vec<us> vec;
    us ite = S - 1;
    inl void init() { ite = S - 1; vec.clear(); }
    inl us nt() {
        if(vec.empty()) ret ++ite;
        el { us res = vec.back(); vec.pop_back(); ret res; }
    }
    inl void gc(us idx) { vec.push_back(idx); }
    inl us operator++() { ret nt(); }
    inl us end() { ret ite + 1; }
    inl us sz() { ret ite + 1 - S; }
};