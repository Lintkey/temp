// 多项式基础概念：n-1次多项式最高次项为n-1次，至多有n个系数
//              大小为n的点值表达式唯一确定一个至多n-1次多项式(可以比n-1小)
// 快速多项式乘法过程：dft(a), dft(b) // 将a, b变成点值表达式 O(nlgn)
//                  a[i] *= b[i]   // 点值表达式乘法 O(n)
//                  idft(a)        // 将a转变回普通表示法 O(nlgn)
// 利用矩阵可以证明，只需反转系数并/len，即可逆变换，故dft和idft可共用一套代码
// 使用方法，调用convolu(A, B, lgl)即可计算AB卷积，返回结果储存在A中，B变为对应的点值表达式
// WARN: 必须确保(1<<lgl)>=预期卷积长度
#pragma once
#include "../base.h"
#include "conv.h"
#include "complex.h"

// len(fx) == 1<<lgl >= sz(fx)
template<is fg, class F>
inl void FFT(CT<F> *arr, con us lgl) {
    con us LEN = 1 << lgl;
    for(us i=1, j=LEN>>1; i<LEN-1; ++i) { // 顺序倒置
        if(i>j) swap(arr[i], arr[j]); // 交换，i>j保证只交换一次
        for(us l=LEN>>1; (j^=l)<l; l>>=1); // 对j做反bit加
    }

    con CT<F> *ED = arr + LEN; CT<F> w, wn;
    for(us l=1, m=1; (l<<=1)<=LEN; m=l) {
        con F ag = PI<F>() / m;
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
inl void DFT(CT<F> *fc, con us lgl) { ret FFT<1>(fc, lgl); }

template<class F>
inl void IDFT(CT<F> *fx, con us lgl) {
    FFT<-1>(fx, lgl); con us LEN = 1 << lgl;
    for(us i=0; i<LEN; ++i) fx[i].real(fx[i].real()/LEN);
}

template<class F>
inl void convolu(CT<F> *lfc, CT<F> *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DFT(lfc, lgl); IDFT(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] *= rfc[i];
    IDFT(lfc, lgl);
}

// WARN: 此实现未经测试，通常情况下答案要求取模，因此建议使用CDQ_NTT
template<class F, CT<F> *A, CT<F> *B>
inl void CDQ_FFT(CT<F> *f, CT<F> *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    CDQ_FFT<F, A, B>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mem(A+MID-L, 0, len-(MID-L));
    for(us i=L; i<MID; ++i) A[i-L] = f[i];
    memcpy(B, g+1, len*sf(CT<F>));
    convolu(A, B, lgl);
    for(us i=MID; i<R; ++i) f[i] += A[i-L-1];
    CDQ_FFT<F, A, B>(f, g, MID, R);
}