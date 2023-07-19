// 复数实现，此版本已接近最优，大部分参考自std
#pragma once
#include "../base.h"

template<class F>
struct CT {
    F r, i;
    cer CT(con F &r=F(), con F &i=F()):r(r), i(i){}
    cer F real() con { ret r; }
    cer F imag() con { ret i; }
    void real(con F &_r) { r=_r; }
    void imag(con F &_i) { i=_i; }
    CT operator~() con { ret CT(r, -i); }
    CT operator-() con { ret CT(-r, -i); }
    CT &operator=(con CT &rh) { ret r=rh.r, i=rh.i, *this; }
    CT &operator+=(con CT &rh) { ret r+=rh.r, i+=rh.i, *this; }
    CT &operator-=(con CT &rh) { ret r-=rh.r, i-=rh.i, *this; }
    CT &operator*=(con CT &rh) {
        con F tr = r * rh.r - i * rh.i;
        ret i=r*rh.i+i*rh.r, r=tr, *this;
    }
};

template<class F>
CT<F> operator+(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r+rc.r, lc.i+rc.i); }
template<class F>
CT<F> operator-(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r-rc.r, lc.i-rc.i); }
template<class F>
CT<F> operator*(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r*rc.r-lc.i*rc.i, lc.r*rc.i+lc.i*rc.r); }