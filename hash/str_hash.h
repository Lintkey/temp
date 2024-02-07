#include "../base.h"
#include "../math/pow.h"

template<us B>
struct StrHash {
    vector<us> hs, bp;
    template<class T>
    void init(T *s, us sz) {
        hs.resize(sz+1, 0);
        for(us i=0; i<sz; ++i)
            hs[i+1] = hs[i]*B+s[i];
    }
    template<us *BP>
    us sub(us l, us r) { ret hs[r]+hs[l]*(-BP[r-l]); }
    us sub(us l, us r) { ret hs[r]+hs[l]*(-mpow(B, r-l)); }
    us &operator[](us idx) { ret hs[idx]; }
};

template<us B, us M>
struct MStrHash {
    vector<us> hs, bp;
    template<class T>
    void init(T *s, us sz) {
        hs.resize(sz+1, 0);
        for(us i=0; i<sz; ++i)
            hs[i+1] = (hs[i]*ul(B)+s[i]) % M;
    }
    template<us *MBP>
    us sub(us l, us r) { ret (hs[r]+hs[l]*ul(M-MBP[r-l])) % M; }
    us sub(us l, us r) { ret (hs[r]+hs[l]*ul(M-mpow<M>(B, r-l))) % M; }
    us &operator[](us idx) { ret hs[idx]; }
};