// 原理：可以考虑找到每个数的最小质因数，以避免冗余查找
// 对于i*pris[j]，如果pris[j]不是i的质因数，那么pris[j]一定是目标的最小质因数
// 如pris[j]是i的质因数，那么对i*pris[j+k]的枚举就是冗余的，因此直接跳出
#pragma once
#include "../base.h"

inl us prim(con us MX, us *pris, bool *vis) {
    us cnt = 0;
    mem(vis, 0, MX+1);
    for(us i=2; i<=MX; ++i) {
        if(!vis[i]) pris[cnt++] = i;
        for(us j=0; j<cnt; ++j) {
            if(ul(i)*pris[j]>MX) break;
            vis[i*pris[j]] = 1;
            if(i%pris[j] == 0) break;
        }
    }
}