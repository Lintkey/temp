#pragma once
#include "../base.h"

template<class T, class N>
T mpow(T x, N nth) {
    T res(x!=0||nth==0);
    for(; nth; x*=x, nth>>=1)
        if(nth&1) res *= x;
    ret res;
}

template<class N>
us mpow(ul x, N nth, con us M) {
    ul res(x!=0||nth==0);
    for(; nth; x=(x*x)%M, nth>>=1)
        if(nth&1) res = (res*x)%M;
    ret res;
}

// 常量加速
template<us M, class N=us>
us mpow(ul x, N nth=M-2) { // 默认求逆元
    ul res(x!=0||nth==0);
    for(; nth; x=(x*x)%M, nth>>=1)
        if(nth&1) res = (res*x)%M;
    ret res;
}
