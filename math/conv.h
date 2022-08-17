#pragma once
#include "../base.h"

template<class F=fl> inl cer F PI() { ret 3.141592653589793238463; }
template<> inl cer fs PI<fs>() { ret 3.14159265358979f; }
template<> inl cer fx PI<fx>() { ret 3.141592653589793238462643383279502884L; }