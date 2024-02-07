// ERROR: 对于交互题，**不能**使用该缓冲快读!(fread没有输入检测，有可能会出现交互机未来得及输入就判定EOF的情况)
// 带缓冲快读，(unsigned/signed)整形、有图形char、string和char[]已经过测试
// TODO: double, float
#pragma once
#include "base.h"

cer us IBUF_LEN = 1 << 16;
char ibuf[1<<16], *ifr = ibuf, *ied = ibuf;
#define fread() (ied=(ifr=ibuf)+fread(ibuf,1,IBUF_LEN,stdin),ifr==ied) // 单次fread不会等待输入
#define ischar(c) (!isspace(c)&&c!=EOF)
char gc() { ret (ifr==ied && fread()) ? EOF : *(ifr++); } // 读取并弹出字符(类似getchar)
char gr() { ret (ifr==ied && fread()) ? EOF : *ifr; } // 读取字符
char fit() { whi(isspace(gr())) ++ifr; ret gr(); } // 将空字符丢弃，并返回第一个非空字符或EOF
#undef fread

template<class T> T &fin(T &v) {
    is c = v = 0; bool f = fit()=='-'; ifr += f;
    whi(isdigit(c=gc())) v = v*10 + (c ^ 48);
    ret f ? (v=-v) : v;
}

template<class T> void fin(T arr[], us n) {
    for(us i=0; i<n; ++i) fin(arr[i]);
}

// 读取非空字符(建议手动gc()，这个只是简写)
template<> char &fin(char &v) { ret fit(), v = gc(); }

// C++式字符串，如情况允许，建议使用C式字符串
template<> string &fin(string &str) {
    str.clear();
    whi(isspace(gr())) ++ifr;
    for(char *fp; ischar(gr()); ifr = fp) {
        for(fp=ifr; fp<ied&&ischar(*fp); ++fp);
        str.append(ifr, fp - ifr);
    } ret str;
}

// C式字符串
char *fin(char *ch) {
    char *cp = ch;
    whi(isspace(gr())) ++ifr;
    for(char *fp; ischar(gr()); ifr = fp) {
        for(fp=ifr; fp<ied&&ischar(*fp); ++fp);
        con us SZ = fp - ifr;
        mec(ifr, cp, SZ);
        cp += SZ;
    } ret *cp = '\0', ch;
}

template<class T=us> T fin() { T val; ret fin(val); }