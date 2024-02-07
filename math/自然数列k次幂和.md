$$
\begin{align}
\sum i^1&=\frac12n(n+1)\\
\sum i^2&=\frac16n(n+1)(2n+1)\\
\sum i^3&=\frac14n^2(n+1)^2\\
\sum i^4&=\frac1{30}n(n+1)(2n+1)(3n^2+3n-1)\\
\sum i^5&=\frac1{12}n^2(n+1)^2(2n^2+2n-1)\\
\sum i^6&=\frac1{42}n(n+1)(2n+1)(3n^4+6n^3-3n+1)
\end{align}
$$

多项式版本，简记 ${\rm poly}(a_1,a_2,\cdots,a_k)=\sum_{i=1}^ka_in^i$：

$$
\begin{align}
\sum i^1&={\rm poly}\left(\frac12,\frac12\right)\\
\sum i^2&={\rm poly}\left(\frac16,\frac12,\frac13\right)\\
\sum i^3&={\rm poly}\left(0,\frac14,\frac12,\frac14\right)\\
\sum i^4&={\rm poly}\left(-\frac1{30},0,\frac13,\frac12,\frac15\right)\\
\sum i^5&={\rm poly}\left(0,-\frac1{12},0,\frac5{12},\frac12,\frac16\right)\\
\sum i^6&={\rm poly}\left(\frac1{42},0,-\frac16,0,\frac12,\frac12,\frac17\right)
\end{align}
$$

结论是 $n$ 次幂求和公式为 $n+1$ 阶无常数项多项式，因此待定系数法求 $n+1$ 阶齐次方程即可计算多项式系数(似乎没啥用)