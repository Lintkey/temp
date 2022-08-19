// WARN: 对于交互题，请使用普通快读!(印象中缓冲式快读不会等待stdin更新，况且交互题IO频繁，没必要开缓冲)
// WARN: string和char *仅经过简单测试
// 带缓冲快读，(unsigned/signed)整形和有图形char已经过测试，
// TODO: double, float
#pragma once
#include "base.h"

cer us MAXB = 1 << 20;
char fbuf[MAXB], *fr = fbuf, *ed = fbuf;
#define fread() (ed=(fr=fbuf)+fread(fbuf,1,MAXB,stdin),fr==ed)
#define ischar(c) (!isspace(c))
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

template<>
inl string &fin(string &str) {
    str.clear();
    for(char *fp; fit()!=EOF;) {
        for(fp=fr; fp<ed&&ischar(*fp); ++fp){}
        str.append(fr, fp - fr);
        if((fr=fp)!=ed) break;
    } ret str;
}

inl char *fin(char *ch) {
    char *cp = ch;
    for(char *fp; fit()!=EOF;) {
        for(fp=fr; fp<ed&&ischar(*fp); ++fp){}
        con us SZ = fp - fr;
        memcpy(cp, fr, SZ*sf(char)); cp += SZ;
        if((fr=fp)!=ed) break;
    } ret *cp = '\0', ch;
}