#pragma once
#include "base.h"
#define prez(x,ll...) __builtin_clz ## ll (x)
#define sufz(x,ll...) __builtin_ctz ## ll (x)
#define cnto(x,ll...) __builtin_popcount ## ll (x)
template<class T> T lowb(T x) { ret x&-x; }