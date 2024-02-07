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
void NTT(us *arr, us lgl) {
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

template<us M, us G> void DNT(us *fc, us lgl) { NTT<M, G>(fc, lgl); }

template<us M = 998244353, us G = 3, us GI = 332748118>
void mconv(us *lfc, us *rfc, con us lgl) {
    con us LEN = 1 << lgl;
    DNT<M, G>(lfc, lgl); DNT<M, G>(rfc, lgl);
    for(us i=0; i<LEN; ++i) lfc[i] = ul(lfc[i]) * rfc[i] % M;
    DNT<M, GI>(lfc, lgl);
    con us inv = mpow<M>(LEN);
    for(us i=0; i<LEN; ++i) lfc[i] = ul(lfc[i]) * inv % M;
}

// 取模递归卷积
template<us *BUF1, us *BUF2, us M = 998244353, us G = 3, us GI = 332748118>
void cdq_NTT(us *f, con us *g, con us L, con us R) {
    if(L+1==R) ret;
    con us MID = (L+R) >> 1, LEN = R - L;
    cdq_NTT<BUF1, BUF2, M, G, GI>(f, g, L, MID);
    us lgl = 0, len = 1;
    whi(len<LEN) ++lgl, len<<=1;
    mes(BUF1+MID-L, len-(MID-L));
    for(us i=L; i<MID; ++i) BUF1[i-L] = f[i];
    mec(g+1, BUF2, len);
    mconv<M, G, GI>(BUF1, BUF2, lgl);
    for(us i=MID; i<R; ++i) f[i] = (ul(f[i]) + BUF1[i-L-1]) % M;
    cdq_NTT<BUF1, BUF2, M, G, GI>(f, g, MID, R);
}

// 求f的逆，结果存在g中，注意lgl必须是2次幂
template<us *BUF, us M = 998244353, us G = 3, us GI = 332748118>
void poly_inv(us *f, us *g, us lgl) {
    if(!~lgl) { g[0] = mpow<M>(f[0]); ret; }
    poly_inv<BUF, M, G, GI>(f, g, lgl-1);
    con us len = 1 << lgl, elen = len << 1;
    mec(f, BUF, len);
    DNT<M, G>(BUF, lgl + 1); DNT<M, G>(g, lgl + 1);
    for(us i=0; i<elen; ++i)
        g[i] = ul((M+2-ul(ul(BUF[i])*g[i]%M))%M)*g[i] % M;
    DNT<M, GI>(g, lgl + 1);
    con us inv = mpow<M>(elen);
    for(us i=0; i<len; ++i) g[i] = ul(g[i]) * inv % M;
    mes(g+len, len);
}