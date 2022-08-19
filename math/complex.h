// 复数实现，此版本已接近最优，大部分参考自std
#pragma once
#include "../base.h"

template<class F>
struct CT {
    F r, i;
    inl cer CT(con F &r=F(), con F &i=F()):r(r), i(i){}
    inl cer F real() con { ret r; }
    inl cer F imag() con { ret i; }
    inl void real(con F &_r) { r=_r; }
    inl void imag(con F &_i) { i=_i; }
    inl CT operator~() con { ret CT(r, -i); }
    inl CT operator-() con { ret CT(-r, -i); }
    inl CT &operator=(con CT &rh) { ret r=rh.r, i=rh.i, *this; }
    inl CT &operator+=(con CT &rh) { ret r+=rh.r, i+=rh.i, *this; }
    inl CT &operator-=(con CT &rh) { ret r-=rh.r, i-=rh.i, *this; }
    inl CT &operator*=(con CT &rh) {
        con F tr = r * rh.r - i * rh.i;
        ret i=r*rh.i+i*rh.r, r=tr, *this;
    }
};

template<class F>
inl CT<F> operator+(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r+rc.r, lc.i+rc.i); }
template<class F>
inl CT<F> operator-(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r-rc.r, lc.i-rc.i); }
template<class F>
inl CT<F> operator*(con CT<F> &lc, con CT<F> &rc) { ret CT<F>(lc.r*rc.r-lc.i*rc.i, lc.r*rc.i+lc.i*rc.r); }