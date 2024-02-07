// 注意浮点转整形有精度误差，可以floor(x+0.5)解决
#pragma once
#include "../base.h"
#include "conv.h"
#include "complex.h"

// len(fx) == 1<<lgl >= sz(fx)
template<is fg, class F>
void FFT(CT<F> *arr, con us lgl) {
    con us LEN = 1 << lgl;
    for(us i=1, j=LEN>>1; i<LEN-1; ++i) { // 顺序倒置
        if(i>j) swap(arr[i], arr[j]); // 交换，i>j保证只交换一次
        for(us l=LEN>>1; (j^=l)<l; l>>=1); // 对j做反bit加
    }

    con CT<F> *ED = arr + LEN; CT<F> w, wn;
    for(us l=1, m=1; (l<<=1)<=LEN; m=l) {
        con F ag = PI<F> / m;
        wn.real(cos(ag)); wn.imag(sin(fg * ag));
        for(CT<F> *p=arr; p!=ED; p+=l) {
            w.real(1); w.imag(0);
            for(us i=0; i<m; ++i) {
                con CT<F> t = w * p[m+i];
                p[m+i] = p[i] - t;
                p[i] += t;
                w *= wn;
            }
        }
    }
}

template<class F> void DFT(CT<F> *fc, con us lgl) { ret FFT<1>(fc, lgl); }
template<class F> void IDFT(CT<F> *fx, con us lgl) { FFT<-1>(fx, lgl); }

// (1<<lgl): 卷积结果的长度(N1+N2-1,对齐到2次幂)
// 计算lfc与rfc的卷积，rfc -> DFT(rfc)，lfc -> (*,lfc,rfc)
template<class F>
void conv(CT<F> *lfc, CT<F> *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DFT(lfc, lgl); DFT(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] *= rfc[i];
    IDFT(lfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i].real(lfc[i].real()/LEN);
}

// 求解f[i] = sum(1,i,f[i-j]*g[j])型递归卷积 f[0] = 1
// 例如多项式求逆 f'[0] = 1/f[0],f'[i]=sum(1,i,f'[i-j]*f[j])
// WARN: 此实现未经测试，通常情况下答案要求取模，因此建议使用`cdq_mconvolu`
template<class F, CT<F> *BUF1, CT<F> *BUF2>
void rec_conv(CT<F> *f, CT<F> *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    rec_conv<F, BUF1, BUF2>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mes(BUF1+MID-L, len-(MID-L));
    for(us i=L; i<MID; ++i) BUF1[i-L] = f[i];
    mec(g+1, BUF2, len);
    conv(BUF1, BUF2, lgl);
    for(us i=MID; i<R; ++i) f[i] += BUF1[i-L-1];
    rec_conv<F, BUF1, BUF2>(f, g, MID, R);
}