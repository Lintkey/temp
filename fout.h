// WARN: 对于交互题，建议使用printf!(交互题IO频繁，没必要开缓冲)
// 欲手动刷新缓冲可以执行fout()
#pragma once
#include "base.h"

char obuf[MAXB], *ofr = obuf; cer char *oed = obuf+MAXB;
#define fwrite(SZ) fwrite(obuf, 1, SZ, stdout), ofr=obuf
inl void pc(char c) { if(ofr==oed) fwrite(MAXB); *ofr++ = c; }
inl void fout() { fwrite(ofr-obuf); } // 类似flush
struct AF{ ~AF() { fout(); } } auto_fout; // 结束时自动fout
#undef fwrite

template<class T>
inl void fout(con T &v) {
    stc char cache[40];
    stc us top = 40; T x;
    if(v<0) { pc('-'); x=-v; } else x=v;
    do cache[--top] = (v % 10) ^ 48; whi(v/=10);
    whi(top<40) pc(cache[top++]);
}

template<>
inl void fout(con string &str) {
    con us SZ = str.size();
    for(us i=0; i<SZ; ++i) pc(str[i]);
    // for(auto c : str) pc(c);
}

inl void fout(con char *ch) { whi(*ch!='\0') pc(*ch++); }