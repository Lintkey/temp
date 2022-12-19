#include "../base.h"

template<class U, class I>
void exgcd(U a, U b, I &x, I &y) {
    if(b) {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    } else x = 1, y = 0;
}