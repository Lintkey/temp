#pragma once
#include "../base.h"

// 对反复开辟删除碎片空间可采用此做法
template<us S=0>
struct pit {
    vector<us> vec;
    us ite = S - 1;
    void init() { ite = S - 1; vec.clear(); }
    us nt() {
        if(vec.empty()) ret ++ite;
        else { us res = vec.back(); vec.pop_back(); ret res; }
    }
    void gc(us idx) { vec.push_back(idx); }
    us operator++() { ret nt(); }
    us end() { ret ite + 1; }
    us sz() { ret ite + 1 - S; }
};