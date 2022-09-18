#pragma once
#include <bits/stdc++.h>
#define sf(T) sizeof(T)
#define el else
#define ef(...) else if(__VA_ARGS__)
#define inl inline
#define stc static
#define con const
#define cer constexpr
#define ret return
#define var auto
#define let const auto
#define whi(...) while(__VA_ARGS__)
using namespace std;
using ic = char;
using is = int;
using il = long long;
using ix = __int128;
using uc = unsigned char;
using us = unsigned int;
using ul = unsigned long long;
using ux = unsigned __int128;
using fs = float;
using fl = double;
using fx = long double;
template<class T> inl cer T UINF() { ret T(-1); }
template<class T> inl cer T INF() { ret T(0x3f3f3f3f3f3f3f3f); }
cer con char *ANS[] = {"F", "T"};
cer us MAXB = 1 << 20;

#define ctz(x) __builtin_ctz(x)
#define popcount(x) __builtin_popcount(x)
template<class T> inl void mem(T *arr, us b, us n) { memset(arr, b, n * sf(T)); }
template<class T> inl void tmx(T &lhs, con T &rhs) { if(rhs>lhs) lhs = rhs; }
template<class T> inl void tmn(T &lhs, con T &rhs) { if(rhs<lhs) lhs = rhs; }