#include "../base.h"

// 注意默认填了一个非法字符，映射到-1
template<us LEN, us CSZ=26>
struct PAM {
    static cer us _LEN = LEN+2;
    static cer us _CSZ = CSZ+1;
    us len[_LEN], fil[_LEN], cnt[_LEN];
    us to[_LEN][_CSZ];
    us sz, ls;
    basic_string<us> str;
    void push_node(us l, us f) {
        len[sz] = l; fil[sz] = f;
        cnt[sz] = 0; mes(to[sz++], _CSZ);
    }
    void init() {
        sz = ls = 0;
        push_node(0, 1);
        push_node(-1, 0);
        str = {us(-1)};
    }
    void push(us key) {
        us l = str.length(), f=ls;
        str.push_back(key);
        whi(str[l-len[f]-1]!=key) f = fil[f];
        if(!to[f][key]) {
            us u = fil[f];
            whi(str[l-len[u]-1]!=key) u = fil[u];
            // to[f][key]放后面使f==1时fil=to[1][key]=0
            push_node(len[f]+2, to[u][key]);
            to[f][key] = sz-1;
        }
        ls = to[f][key];
        ++cnt[ls];
    }
};