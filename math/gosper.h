// 原理:
// 最低位的01变10，其后连续的1移动到低位
// bs是01变10后高位的状态(除去其后连续的1)
// bs^cur是操作后受影响的数位状态(1表示反转)
// 易知popcount(bs^cur)-2即是其后连续的1的个数
// bs^cur前导零个数与lb相同，因此直接 >> (ctz(lb)+2)可移动连续1至低位
// cur     lb      bs      bs^cur
// 010110  000010  011000  001110

// 另附上cout打印二进制的方法
// template<class T=us> using bin = bitset<(sf(T)<<3)>;
// cout << bin(v) << endl;
#include "../base.h"

// C_n^k 获取n选k状压状态(从小到大)
template<class T=us>
vector<T> gosper(con us n, con us k) {
    assert(n&&n>=k&&n<=(sf(T)<<3)); // 防止超限
    vector<T> res;
    T cur = (T(1)<<k) - 1;
    T lim = cur << (n-k);
    whi(cur != lim) {
        res.push_back(cur);
        con T lb = cur & -cur, bs = cur + lb;
        cur = ((bs ^ cur) >> (ctz(lb)+2)) | bs;
    } res.push_back(cur);
    ret res;
}
