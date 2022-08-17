#include "../base.h"

template<class T>
inl T pow(T x, us nth) {
    T res(1);
    for(; nth; x*=x, nth>>=1)
        if(nth&1) res *= x;
    ret res;
}

template<class N>
inl us mpow(con us x, N nth, con us M) {
    ul res(1), bs(x);
    for(; nth; bs=(bs*bs)%M, nth>>=1)
        if(nth&1) res = (res*bs)%M;
    ret res;
}

// 常量加速
template<us M, class N>
inl us mpow(con us x, N nth) {
    ul res(1), bs(x);
    for(; nth; bs=(bs*bs)%M, nth>>=1)
        if(nth&1) res = (res*bs)%M;
    ret res;
}