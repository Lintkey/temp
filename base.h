#pragma once
#include <bits/stdc++.h>
using namespace std;
#define sf sizeof
#define con const
#define cer constexpr
#define ret return
#define let const auto
#define whi while
using is = int32_t;
using il = int64_t;
#define ix __int128_t
using us = uint32_t;
using ul = uint64_t;
#define ux __uint128_t
using fs = double;
using fl = long double;
#ifndef EXT
    template<class T> using gque = std::priority_queue<T>;
    template<class T> using lque = std::priority_queue<T, vector<T>, greater<>>;
#endif

template<class T=is> cer T INF = T(0x3f3f3f3f3f3f3f3f);
extern con us MOD;

template<class T> void mec(con T *src, T *dst, us n) { memcpy(dst, src, n*sf(T)); }
template<class T> void mes(T *arr, us n=1, us b=0) { memset(arr, b, n * sf(T)); }
template<class T> void tmx(T &lhs, con T &rhs) { if(rhs>lhs) lhs = rhs; }
template<class T> void tmn(T &lhs, con T &rhs) { if(rhs<lhs) lhs = rhs; }
template<class T> T md(T x) { ret T(x % MOD); }