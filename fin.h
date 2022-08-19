// WARN: 对于交互题，**请使用普通快读!**(印象中缓冲式快读不会等待stdin更新，况且交互题IO频繁，没必要开缓冲)
// WARN: string和char *仅经过简单测试
// 带缓冲快读，(unsigned/signed)整形和有图形char已经过测试，
// TODO: double, float
#pragma once
#include "base.h"

char ibuf[MAXB], *ifr = ibuf, *ied = ibuf;
#define fread() (ied=(ifr=ibuf)+fread(ibuf,1,MAXB,stdin),ifr==ied)
#define ischar(c) (!isspace(c))
inl is gc() { ret (ifr==ied && fread()) ? EOF : *(ifr++); } // 读取并弹出字符(类似getchar)
inl is gr() { ret (ifr==ied && fread()) ? EOF : *ifr; } // 读取字符
inl is fit() { whi(isspace(gr())) ++ifr; ret gr(); } // 将空字符丢弃，并返回第一个非空字符或EOF
#undef fread

template<class T>
inl T &fin(T &v) {
    is c = v = 0; bool f = fit()=='-'; ifr += f;
    whi(isdigit(c=gc())) v = v*10 + (c ^ 48);
    ret f ? (v=-v) : v;
}

template<> // 读取非空字符(建议手动gc()，这个只是简写)
inl char &fin(char &v) { ret fit(), v = gc(); }

template<>
inl string &fin(string &str) {
    str.clear();
    for(char *fp; fit()!=EOF;) {
        for(fp=ifr; fp<ied&&ischar(*fp); ++fp){}
        str.append(ifr, fp - ifr);
        if((ifr=fp)!=ied) break;
    } ret str;
}

inl char *fin(char *ch) {
    char *cp = ch;
    for(char *fp; fit()!=EOF;) {
        for(fp=ifr; fp<ied&&ischar(*fp); ++fp){}
        con us SZ = fp - ifr;
        memcpy(cp, ifr, SZ*sf(char)); cp += SZ;
        if((ifr=fp)!=ied) break;
    } ret *cp = '\0', ch;
}