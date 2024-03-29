给定两个正整数 $a,b$，求在 $[a,b]$ 中的所有整数中，每个数码（digit）各出现了多少次。

设上界有 $len$ 位，第 $i$ 位为 $a[i]$

1. 处理出存在有效前导且无限制时，后i位数字对单种数码的贡献 $dp[i]=10*dp[i-1]+10^{i-1}$，前项是当前数位对前 $i-1$ 位的贡献，后项是前 $i-1$ 位对当前位的贡献
2. 从高到低枚举 $i$ 计算高 $len-i$ 位贴近上界时，第 $i$ 位和低 $i-1$ 位的贡献
   + 高 $len-i$ 位贴近上界，第 $i$ 位比上界 $a[i]$ 小时，第 $i$ 位贡献为：$10^{i-1}$
   + 高 $len-i$ 位与第 $i$ 位均贴近上界时，第 $i$ 位贡献为：$n\mod 10^i + 1$
   + 高 $len-i$ 位贴近上界时，第 $i$ 位能取 $[0,a[i])$，因此低 $i-1$ 位贡献为：$dp[i-1]*a[i]$
   + 由于额外统计了当前位是首位前导 $0$ 的贡献，数码 $0$ 减去 $10^{i-1}$

> 额外统计是因为 $i==len$ 时一、二步统计了每一位是首位前导0(包括单个0)的贡献，因此减去 $\sum_{i=1}^{len}10^{i-1}$ 即可，放进循环里就是每次减去 $10^{i-1}$

## 总结

+ 前 $len-i$ 贴近上界时，第 $i$ 位的贡献
+ 前 $len-i$ 与第 $i$ 位均贴近上界时，第 $i$ 位的贡献
+ 前 $len-i$ 贴近上界时，低 $i-1$ 位的贡献
+ 除去无效统计，例如前导0