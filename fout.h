// WARN: 对于交互题，建议直接使用cout、printf(交互题IO频繁，没必要开缓冲)
// 欲手动刷新缓冲可以执行fout()，可刷新全部缓冲
// TIP: 此实现自带结束时自动缓冲，可以不用在最后执行fout()
#pragma once
#include "base.h"

char obuf[MAXB], *ofr = obuf; cer char *oed = obuf+MAXB;
#define fwrite(SZ) fwrite(obuf, 1, SZ, stdout), ofr=obuf
void pc(char c) { if(ofr==oed) fwrite(MAXB); *ofr++ = c; }
void fout() { fwrite(ofr-obuf); fflush(stdout); } // 刷新obuf->自带缓冲->stdout
struct AF{ ~AF() { fout(); } } auto_fout; // 结束时自动fout

template<class T> void fout(con T &v) {
    stc char cache[40];
    stc us top = 40; T x;
    if(v<0) { pc('-'); x=-v; } else x=v;
    do cache[--top] = (x % 10) ^ 48; whi(x/=10);
    whi(top<40) pc(cache[top++]);
}

// C式字符串简单输出，较慢
void fout(con char *ch) { whi(*ch!='\0') pc(*ch++); }

// TIM 分割输出次数，此模板参数用于编译器展开循环，一般设定为MAXL/MAXB+2
// 如果总输出少的话可以直接设定为1
template<us TIM=2>
void fout(con char *ch, us sz) {
    for(us i=0, s; i<TIM; ++i) {
        sz -= s = min(us(oed-ofr), sz);
        memcpy(ofr, ch, s*sf(char));
        if(ch+=s, (ofr+=s)!=oed) ret;
        else fwrite(MAXB);
    }
}

// TIM 分割输出次数，此参数用于编译器展开循环
template<us TIM=2>
void fout(con string &str) { fout<TIM>(str.c_str(), str.size()); }
#undef fwrite