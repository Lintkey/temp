// WARN: 出于效率考虑，初始化时并未对初始值取模，请手动取模 v.add(0);
// WARN: 为了防止误用，未实现输入重载，但是可以直接输出
// TIP: 如欲加速，请尽量使用同类型对象作为运算对象(MT += MT)，而不是(MT += T)
// TIP: 另外，对于用不到的成员函数，也可删除以加速
#pragma once
#include "../base.h"

// V3.0 M可变更模数
// U: 乘法提升时要用，避免乘法溢出, T=us, U=ul; T=ul, U=ix
template<class T, con T &M, class U=ul>
struct DMT {
    T raw;
    inl cer DMT(con T _raw=T()) : raw(_raw) {}
    inl cer operator T() con { ret raw; }
    inl cer void add(con DMT &r) { raw+=r.raw; if(raw>=M) raw-=M; }
    inl cer void sub(con DMT &r) { if(r.raw>raw) raw+=M-r.raw; else raw-=r.raw; }
    inl cer void mul(con DMT &r) { raw = (U(raw) * r.raw)%M; }
    inl DMT operator-() { DMT r; ret r.raw=M-raw, r; }
    inl DMT &operator=(con DMT &r) { ret raw=r.raw, *this; }
    inl DMT &operator+=(con DMT &r) { ret add(r), *this; }
    inl DMT &operator-=(con DMT &r) { ret sub(r), *this; }
    inl DMT &operator*=(con DMT &r) { ret mul(r), *this; }
    friend inl DMT operator+(DMT l, con DMT &r) { ret l.add(r), l; }
    friend inl DMT operator-(DMT l, con DMT &r) { ret l.sub(r), l; }
    friend inl DMT operator*(DMT l, con DMT &r) { ret l.mul(r), l; }
};

template<con us &M>
using dms = DMT<us, M>;
template<con ul &M>
using dml = DMT<ul, M, ix>;

// V1.0 静态M模数(相比起可变模数会快一点点)
// U: 乘法提升时要用，避免乘法溢出, T=us, U=ul; T=ul, U=ix
template<class T, T M, class U=ul>
struct MT {
    T raw;
    inl cer MT(con T _raw=T()) : raw(_raw) {}
    inl cer operator T() con { ret raw; }
    inl cer void add(con MT &r) { raw+=r.raw; if(raw>=M) raw-=M; }
    inl cer void sub(con MT &r) { if(r.raw>raw) raw+=M-r.raw; else raw-=r.raw; }
    inl cer void mul(con MT &r) { raw = (U(raw) * r.raw)%M; }
    inl MT operator-() { MT r; ret r.raw=M-raw, r; }
    inl MT &operator=(con MT &r) { ret raw=r.raw, *this; }
    inl MT &operator+=(con MT &r) { ret add(r), *this; }
    inl MT &operator-=(con MT &r) { ret sub(r), *this; }
    inl MT &operator*=(con MT &r) { ret mul(r), *this; }
    friend inl MT operator+(MT l, con MT &r) { ret l.add(r), l; }
    friend inl MT operator-(MT l, con MT &r) { ret l.sub(r), l; }
    friend inl MT operator*(MT l, con MT &r) { ret l.mul(r), l; }
};

template<us M>
using ms = MT<us, M>;
template<ul M>
using ml = MT<ul, M, ix>;