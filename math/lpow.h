#include "../base.h"

// WARN: 该结构体使用基于上下文，请注意使用方法
// 用于O(1)求出给定a和m时，任意a的幂次%m的值
// 使用前init(a, m)，询问que(p)获取(a^p)%m
template<us SQT_L>
struct LPow {
    us SQT_M, PHI_M, M, vals[2][SQT_L];
    void init(ul a, us m) {
        SQT_M = ceil(sqrt(M=PHI_M=m));
        for(us i=2; i*i<=m; ++i)
            if(m%i==0) {
                (PHI_M /= i) *= (i-1);
                whi(m%i==0) m /= i;
            }
        vals[0][0] = vals[1][0] = 1;
        for(us i=1; i<SQT_M; ++i)
            vals[0][i] = a * vals[0][i-1] % M;
        (a *= vals[0][SQT_M-1]) %= M;
        for(us i=1; i<SQT_M; ++i)
            vals[1][i] = a * vals[1][i-1] % M;
    }

    us que(ul p) {
        us b = (p %= PHI_M) / SQT_M; p -= (b * SQT_M);
        ret ul(vals[0][p]) * vals[1][b] % M;
    }
};