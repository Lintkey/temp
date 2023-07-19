#pragma once
#include "../base.h"

template<class T>
T pow(T x, us nth) {
    T res(x!=0||nth==0);
    for(; nth; x*=x, nth>>=1)
        if(nth&1) res *= x;
    ret res;
}

template<class N>
us mpow(con us x, N nth, con us M) {
    ul res(x!=0||nth==0), bs(x);
    for(; nth; bs=(bs*bs)%M, nth>>=1)
        if(nth&1) res = (res*bs)%M;
    ret res;
}

// 常量加速
template<us M, class N=us>
us mpow(con us x, N nth=M-2) { // 默认可求逆元
    ul res(x!=0||nth==0), bs(x);
    for(; nth; bs=(bs*bs)%M, nth>>=1)
        if(nth&1) res = (res*bs)%M;
    ret res;
}
