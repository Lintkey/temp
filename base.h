#pragma once
#include <bits/stdc++.h>
#define el else
#define sf sizeof
#define ef else if
#define stc static
#define con const
#define cer constexpr
#define ret return
#define var auto
#define let const auto
#define whi while
using namespace std;
using is = int;
using il = long long;
#define ix __int128
using us = unsigned int;
using ul = unsigned long long;
#define ux unsigned __int128
using fs = float;
using fl = double;
using fx = long double;
using Str = string;
template<class T> using Vec = vector<T>;
template<class T> using lque = priority_queue<T, Vec<T>, greater<T>>;
template<class T> using gque = priority_queue<T>;
template<class T=us> cer T UINF = -1;
template<class T=is> cer T INF = T(0x3f3f3f3f3f3f3f3f);
template<class F=fl> cer F EPS = 1e-8;
template<> cer fx EPS<fx> = 1e-12;
cer con char *ANS[] = {"F", "T"};
cer us MAXB = 1 << 16;
// cer fl EPS = 1e-8;
extern con us MOD;

#define ctz(x) __builtin_ctz(x)
#define popcount(x) __builtin_popcount(x)
template<class T> void mem(T *arr, us n=1, us b=0) { memset(arr, b, n * sf(T)); }
template<class T> void tmx(T &lhs, con T &rhs) { if(rhs>lhs) lhs = rhs; }
template<class T> void tmn(T &lhs, con T &rhs) { if(rhs<lhs) lhs = rhs; }
template<class T> T md(T x) { ret T(x % MOD); }