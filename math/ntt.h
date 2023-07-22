// 数论变换的情况下，原根g_n与w_n等价，原因在于 \
// `g^(nl=(m-1)) % mod = 1`, \
// `g_n = g^((m-1)/l) % mod`, `g_n^n % mod = 1` \
// 为了能分治求解，设M=p*(2^k)+1，应有k>=lgl, (2^lgl)>=卷积结果长度 \
// 原根几乎可以随便取，一般建议取3，3^i != 3^j (%mod) \
// 998244353 = 7*17 * 2^23 + 1 \
// 1004535809 = 479 * 2^21 + 1
#pragma once
#include "../base.h"
#include "pow.h"

// len(fx) == 1<<lgl >= sz(fx)
template<us M, us G>
void FNTT(us *arr, us lgl) {
    con us LEN = 1 << lgl;
    for(us i=1, j=LEN>>1; i<LEN-1; ++i) { // 顺序倒置
        if(i>j) swap(arr[i], arr[j]); // 交换，i>j保证只交换一次
        for(us l=LEN>>1; (j^=l)<l; l>>=1); // 对j做反bit加
    }

    con us *ED = arr + LEN; ul g;
    for(us l=1, m=1; (l<<=1)<=LEN; m=l) {
        con us gn = mpow<M>(G, (M-1)/l);
        for(us *p=arr; p!=ED; p+=l) {
            g = 1;
            for(us i=0; i<m; ++i) {
                con us t = (ul(g)*p[m+i])%M;
                p[m+i] = p[i]>=t?p[i]-t:p[i]+(M-t);
                p[i] = p[i]<M-t?p[i]+t:p[i]+(t-M);
                g = (g * gn) % M; // w : ul
            }
        }
    }
}

template<us M, us G> void DNT(us *fc, us lgl) { FNTT<M, G>(fc, lgl); }

// G: 原根, GI: G的逆元`mpow(G, M-2)` \
// (1<<lgl): 卷积结果的长度，包含0次项 \
// WARN: 必须确保M=p*(2^k)+1, k>=lgl
template<us M = 998244353, us G = 3, us GI = 332748118>
void mconvolu(us *lfc, us *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DNT<M, G>(lfc, lgl); DNT<M, G>(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] = ul(lfc[i]) * rfc[i] % M;
    DNT<M, GI>(lfc, lgl);
    con us inv = mpow<M>(LEN);
    for(us i=0; i<LEN; ++i) lfc[i] = ul(lfc[i]) * inv % M;
}

// 递归卷积(NTT版)
template<us *A, us *B, us M = 998244353, us G = 3, us GI = 332748118>
void cdq_mconvolu(us *f, con us *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    cdq_mconvolu<A, B, M, G, GI>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mes(A+MID-L, len-(MID-L));
    for(us i=L; i<MID; ++i) A[i-L] = f[i];
    mec(g+1, B, len);
    mconvolu<M, G, GI>(A, B, lgl);
    for(us i=MID; i<R; ++i) f[i] = (ul(f[i]) + A[i-L-1]) % M;
    cdq_mconvolu<A, B, M, G, GI>(f, g, MID, R);
}