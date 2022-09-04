#include "../base.h"

void exgcd(is a, is b, is &x, is &y) {
    if(b) {
        exgcd(b, b % a, y, x);
        y -= a / b * x;
    } else x = 1, y = 0;
}