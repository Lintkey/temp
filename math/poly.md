## 多项式(在 $\bmod\ x^n$ 意义下)的逆

对于已知系数为 $f[n]$ 的`poly`$F(x)$，其在 $\bmod\ x^m$ 意义下的逆 $G(x)$ 满足：

$$
G(x)F(x)\equiv 1 \pmod{x^m}
$$

$G(x)$ 存在的充要条件是 $f[0]\not=0$

### 递归卷积求解 $O(n\log^2 n)$

设 $G(x)$ 系数为 $g[n]$，结合定义，有：

$$
\begin{align}
G(x)F(x)&=\sum_{i=0}f[i]G(x)x^i=f[0]G(x)+\sum_{i=1}f[i]G(x)x^i\\
&\equiv 1\pmod {x^m}\\
g[0]f[0]&=1
\end{align}
$$

由此可得：

$$
g[n]=\begin{cases}
-f^{-1}[0]\sum_{i=1}^nf[i]g[n-i]&0<n<m\\
f^{-1}[0]&n=0
\end{cases}
$$

$g[n]$ 的公式很明显就是个递归卷积，直接算就行了

### 倍增法 $O(n\log n)$

记 $G_k(x)$ 是 $F(x)\mod x^{2^k}$ 的逆，那么有

$$
\begin{align}
F(x)G_{k+1}(x)-F(x)G_k(x)&\equiv 1-1=0&\pmod {x^{2^k}}\\
G_{k+1}(x)-G_k(x)&\equiv 0&\pmod {x^{2^k}}\\
F(x)(G_{k+1}(x)-G_k(x))^2&\equiv 0&\pmod {x^{2^{k+1}}}\\
G_{k+1}(x)&\equiv G_k(x)(2-F(x)G_k(x))&\pmod {x^{2^{k+1}}}\\
\end{align}
$$

因此从 $G_0=f^{-1}[0]$ 开始不断倍增卷积计算即可

实现类似求递归卷积，不同的是不用计算右节点，因此复杂度降低至 $O(n\log n)$

### 利用求逆算递归卷积 $g[0]=x, g=g*f$

从前面的递归卷积求逆的推导入手，令 $f[0]=0,H(x)=1-F(x)$，则 $G(x)=g[0]H^{-1}(x)$