#pragma once
#include "base.h"

cer us MAXB = 1 << 20;
char fbuf[MAXB], *fr = fbuf, *ed = fbuf;
#define fread() (ed=(fr=fbuf)+fread(fbuf,1,MAXB,stdin),fr==ed)
inl is gc() { ret (fr==ed && fread()) ? EOF : *(fr++); }
inl is gr() { ret (fr==ed && fread()) ? EOF : *fr; }
inl is fit() { whi(isspace(gr())) ++fr; ret gr(); }
#undef fread

template<class T>
inl T &fin(T &v) {
    is c = v = 0; bool f = fit()=='-'; fr += f;
    for(; isdigit(c=gc());) v = v*10 + c - '0';
    ret f ? (v=-v) : v;
}

template<>
inl char &fin(char &v) { ret fit(), v = gc(); }