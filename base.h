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
#define whi(...) while(__VA_ARGS__)
using namespace std;
using is = int;
using il = long long;
using us = unsigned int;
using ul = unsigned long long;
using fs = float;
using fl = double;
#define ix __int128
using fx = long double;
template<class T> inl cer T UINF() { ret T(-1); }
template<class T> inl cer T INF() { ret T(0x3f3f3f3f3f3f3f3f); }
con string ANS[2] = {"NO", "YES"};

template<class T>
inl void mem(T *arr, us b, us n) { memset(arr, b, n * sf(T)); }
