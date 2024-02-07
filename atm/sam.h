#include "../base.h"

// LEN：长度，空间和初始化都是两倍
template<us LEN, us CSZ=26>
struct SAM {
    us len[LEN*2], fil[LEN*2];
    us to[LEN*2][CSZ];
    us sz, ls;
    void init() {
        ls = len[0] = 0;
        mes(to[0], CSZ);
        fil[0] = -1;
        sz = 1;
    }
    void push(us key) {
        us cu = sz++, p = ls;
        len[cu] = len[ls] + 1;
        fil[cu] = 0;
        mes(to[cu], CSZ);
        whi(~p&&!to[p][key]) {
            to[p][key] = cu;
            p = fil[p];
        }

        if(~p) {
            us q = to[p][key];
            if(len[p]+1!=len[q]) {
                us cl = sz++;
                len[cl] = len[p] + 1;
                fil[cl] = fil[q];
                mec(to[q], to[cl], CSZ);
                whi(~p&&to[p][key]==q) {
                    to[p][key] = cl;
                    p = fil[p];
                }
                fil[q] = fil[cu] = cl;
            } else fil[cu] = q;
        } ls = cu;
    }
    us *operator[](us u) { ret to[u]; };
};