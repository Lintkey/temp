// 多项式基础概念：n-1次多项式最高次项为n-1次，至多有n个系数
//              大小为n的点值表达式唯一确定一个至多n-1次多项式(可以比n-1小)
// 快速多项式乘法过程：dft(a), dft(b) // 将a, b变成点值表达式 O(nlgn)
//                  a[i] *= b[i]   // 点值表达式乘法 O(n)
//                  idft(a)        // 将a转变回普通表示法 O(nlgn)
// 利用矩阵可以证明，只需反转系数并/len，即可逆变换，故dft和idft可共用一套代码
#pragma once
#include "../base.h"
#include "conv.h"
#include "complex.h"

// len(fx) == 1<<lgl >= sz(fx)
template<class F>
inl void fft(CT<F> *arr, us lgl, con is fg) {
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
inl void dft(CT<F> *fc, us lgl) { ret fft(fc, lgl, 1); }

template<class F>
inl void idft(CT<F> *fx, us lgl) {
    fft(fx, lgl, -1); con us LEN = 1 << lgl;
    for(us i=0; i<LEN; ++i) fx[i].real(fx[i].real()/LEN);
}