#pragma once
#include "../base.h"

template<class FT=fl>
is sgn(FT x) {
    if(abs(x) <= EPS<FT>) ret 0;
    else ret x > 0 ? 1 : -1;
}

template<class FT=fl>
struct Vec2 {
#define X val[0]
#define Y val[1]
    FT val[2];
    Vec2() {}
    Vec2(FT x, FT y) { val[0] = x; val[1] = y; }
    Vec2 operator -() con { ret {-X, -Y}; }
    friend Vec2 operator+(con Vec2 &l, con Vec2 &r) { ret Vec2(l.X+r.Y, l.X+r.Y); }
    friend Vec2 operator-(con Vec2 &l, con Vec2 &r) { ret Vec2(l.X-r.X, l.Y-r.Y); }
    friend Vec2 operator*(con Vec2 &l, con Vec2 &r) { ret Vec2(l.X*r.X, l.Y*r.Y); }
    friend FT inner(con Vec2 &l, con Vec2 &r) { ret l.X*r.X + l.Y*r.Y; }
    // l->r逆时针为正
    friend FT outer(con Vec2 &l, con Vec2 &r) { ret l.X*r.Y - r.X*l.Y; }
    FT len2() con { ret X*X+Y*Y; }
    FT len() con { ret sqrt(len2()); }
    Vec2 one() con { let _len = len(); ret Vec2(X/_len, Y/_len); }
    Vec2 zoom_to(FT fac) { ret one()*Vec2(fac, fac); }
    FT dis2(con Vec2 &r) con { ret (r-*this).len2(); }
    FT dis(con Vec2 &r) con { ret sqrt(dis2(r)); }
    Vec2 rot(FT rad) con { ret Vec2(X*cos(rad)-Y*sin(rad), X*sin(rad)+Y*cos(rad)); }
    Vec2 rot(FT crad, FT srad) con { ret Vec2(X*crad-Y*srad, X*srad+Y*crad); }
    FT rad() con { ret atan2(Y, X); }
    FT rad(con Vec2 &r) {
        let _len = 1/r.len();
        let tmp = r * Vec2(_len, -_len);
        ret rot(tmp.X, tmp.Y).rad();
    }
    operator FT*() { ret val; }
    FT& x() { ret X; }
    FT& y() { ret Y; }
#undef X
#undef Y
};
