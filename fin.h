// 带缓冲快读，目前仅支持(unsigned/signed)整形和有图形char
#pragma once
#include "base.h"

cer us MAXB = 1 << 20;
char fbuf[MAXB], *fr = fbuf, *ed = fbuf;
#define fread() (ed=(fr=fbuf)+fread(fbuf,1,MAXB,stdin),fr==ed)
inl is gc() { ret (fr==ed && fread()) ? EOF : *(fr++); } // 读取并弹出字符(类似getchar)
inl is gr() { ret (fr==ed && fread()) ? EOF : *fr; } // 读取字符
inl is fit() { whi(isspace(gr())) ++fr; ret gr(); } // 将空字符丢弃，并返回第一个非空字符或EOF
#undef fread

template<class T>
inl T &fin(T &v) {
    is c = v = 0; bool f = fit()=='-'; fr += f;
    for(; isdigit(c=gc());) v = v*10 + c - '0';
    ret f ? (v=-v) : v;
}

template<>
inl char &fin(char &v) { ret fit(), v = gc(); } // 读取非空字符