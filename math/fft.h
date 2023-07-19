// 原理就是从时域对(l-1)次多项式f(t)离散傅立叶变换到频域 \
// 时域O(l^2)卷积对应频域O(2l)乘积 \
// (l-1)次多项式频域带为[0, l)，那么卷积结果的频域带应为[0, 2l-1) \
// 二次优化原理是将分治转化为多次循环，并减少w = e^(2Pik/n)的重复计算
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

template<class F>
void DFT(CT<F> *fc, con us lgl) { ret FFT<1>(fc, lgl); }

template<class F>
void IDFT(CT<F> *fx, con us lgl) {
    FFT<-1>(fx, lgl); con us LEN = 1 << lgl;
    for(us i=0; i<LEN; ++i) fx[i].real(fx[i].real()/LEN);
}

// (1<<lgl): 卷积结果的长度(N1+N2-1,对齐到2次幂)
template<class F>
void convolu(CT<F> *lfc, CT<F> *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DFT(lfc, lgl); IDFT(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] *= rfc[i];
    IDFT(lfc, lgl);
}

// 求解f = f*g型递归卷积
// WARN: 此实现未经测试，通常情况下答案要求取模，因此建议使用`cdq_mconvolu`
template<class F, CT<F> *A, CT<F> *B>
void cdq_convolu(CT<F> *f, CT<F> *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    cdq_convolu<F, A, B>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mem(A+MID-L, len-(MID-L));
    for(us i=L; i<MID; ++i) A[i-L] = f[i];
    memcpy(B, g+1, len*sf(CT<F>));
    convolu(A, B, lgl);
    for(us i=MID; i<R; ++i) f[i] += A[i-L-1];
    cdq_convolu<F, A, B>(f, g, MID, R);
}