#include "../base.h"

template<class U, class I>
void exgcd(U a, U b, I &x, I &y) {
    if(b) {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    } else x = 1, y = 0;
}

template<class I, class U>
U crt(us n, U *a, U *m) {
    I mod = 1, ans = 0;
    for(us i=0; i<n; ++i) mod *= m[i];
    for(us i=0; i<n; ++i) {
        U cum = mod / m[i]; I x, y;
        // x*cum = 1 (mod m[i])
        exgcd(cum, m[i], x, y);
        ans = (ans + I(a[i])*(x*cum % mod)) % mod;
    }
    ret (ans%mod + mod) % mod;
}