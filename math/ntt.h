// 注意，ntt使用前需确保多项式的各系数%=M
// ntt为fft的优化版本，注意，使用的前提是预期多项式系数不大于M(答案要求取质数模则可直接用)
// dft<MOD, G>(A); dft<MOD, G>(B); A = (A*B) % MOD; idft<MOD, GI>(A)
// M(MOD)必须为(2^m)k+1型质数
// G为原根(gcd(G, MOD))，GI为G的逆元
#pragma once
#include "../base.h"
#include "pow.h"

// len(fx) == 1<<lgl >= sz(fx)
template<us M, us G>
inl void NTT(us *arr, us lgl) {
    con us LEN = 1 << lgl;
    for(us i=1, j=LEN>>1; i<LEN-1; ++i) { // 顺序倒置
        if(i>j) swap(arr[i], arr[j]); // 交换，i>j保证只交换一次
        for(us l=LEN>>1; (j^=l)<l; l>>=1); // 对j做反bit加
    }

    con us *ED = arr + LEN; ul w;
    for(us l=1, m=1; (l<<=1)<=LEN; m=l) {
        con us wn = mpow<M>(G, (M-1)/l);
        for(us *p=arr; p!=ED; p+=l) {
            w = 1;
            for(us i=0; i<m; ++i) {
                con us t = (ul(w)*p[m+i])%M;
                p[m+i] = p[i]>=t?p[i]-t:p[i]+(M-t);
                p[i] = p[i]<M-t?p[i]+t:p[i]+(t-M);
                w = (w * wn) % M; // wn : ul
            }
        }
    }
}

template<us M = 998244353, us G = 3>
inl void DFT(us *fc, us lgl) { ret NTT<M, G>(fc, lgl); }

template<us M = 998244353, us GI = 332748118>
inl void IDFT(us *fx, us lgl) {
    NTT<M, GI>(fx, lgl);
    con us LEN = 1 << lgl, inv = mpow<M>(LEN, M-2);
    for(us i=0; i<LEN; ++i) fx[i]=(ul(fx[i])*inv)%M;
}

template<us M = 998244353, us G = 3, us GI = 332748118>
inl void convolu(us *lfc, us *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DFT<M, G>(lfc, lgl); DFT<M, G>(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] = ul(lfc[i]) * rfc[i] % M;
    IDFT<M, GI>(lfc, lgl);
}

// CDQ_NTT用来解决递归式卷积，由于f[i]是递归定义的，因此无法暴力套用NTT
template<us *A, us *B, us M = 998244353, us G = 3, us GI = 332748118>
inl void CDQ_NTT(us *f, con us *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    CDQ_NTT<A, B, M, G, GI>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mem(A+MID-L, len-(MID-L));
    for(us i=L; i<MID; ++i) A[i-L] = f[i];
    memcpy(B, g+1, len*sf(us));
    convolu(A, B, lgl);
    for(us i=MID; i<R; ++i) f[i] = (ul(f[i]) + A[i-L-1]) % M;
    CDQ_NTT<A, B, M, G, GI>(f, g, MID, R);
}