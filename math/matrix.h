#include "../base.h"

#define MAT_FOR(LEN)            \
    for(us i=0; i<LEN; ++i)     \
        for(us j=0; j<LEN; ++j)

template<us LEN, class T>
struct SMat {
    us len; T vals[LEN][LEN];
    inl SMat() {} inl SMat(us n):len(n) { mem(vals, 0, n); }
    inl void init(us n) { len=n; mem(vals, 0, n); }
    inl T *operator[](con us idx) { ret vals[idx]; }
    inl SMat operator*(con SMat &r) con {
        SMat res(len);
        MAT_FOR(len) {
            con T &tmp = vals[i][j];
            for(us k=0; k<len; ++k)
                res[i][k] += tmp * r.vals[j][k];
        } ret res;
    }
    inl SMat operator+(con SMat &r) con {
        SMat res(len);
        MAT_FOR(len) res[i][j] = vals[i][j] + r.vals[i][j];
        ret res;
    }
    inl SMat pow(ul p) con {
        SMat res(len), bas = *this;
        for(us i=0; i<len; ++i) res[i][i] = 1;
        for(; p; p>>=1) {
            if(p&1) res = res * res;
            bas = bas * bas;
        } ret res;
    }
};
#undef MAT_FOR