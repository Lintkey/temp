# `hash`

考虑到情况多变，该库不封装`hash`库，下面给出常用技巧

## 常用中、大质数

```cpp
1145141     // XD
19260817    // 某八位大质数(手动滑稽)
1e9+7/9
```

## 数组`hash`

针对连续有序对象的`hash`，可用于字符串哈希。另外当 $B=1$ 时为集合`hash`

$${\rm hash}(s_{[l,r)})=\big({\rm hash}(s_{[l,r-1)})*B+s[r-1]\big)\mod M$$

该定义可快速求出子对象的`hash`：

$${\rm hash}(s_{[l,r)})=\Big({\rm hash}(s_{[0,r)})+{\rm hash}(s_{[0,l)})*\big(M-(B^{r-l}\bmod M)\big)\Big) \mod M$$

后面一长串是`-hash(0,l)*pow(B,r-l)`，为避免负号及溢出改写成`hash(0,l)*(M-mpow(B,r-l,M))`

## 树`hash` [[参考](https://peehs-moorhsum.blog.uoj.ac/blog/7891)]

$${\rm hash}(u)=\big(1+\sum^{v|{\rm son}(u)}f({\rm hash}(v))\big)\mod M\\$$

引入的 $f$ 用于表征父子关系，因此 $f$ 函数需保证随机映射。一个较好(不容易构造错解)的随机映射函数`rnd_f`如下

```cpp
ul _h(ul x) { ret x*x*x*1145141 + 19260817; }
ul rnd_f(ul x) { ret _h(us(x)) + _h(x>>32); }
```

该定义可用于换根dp：

```cpp
// 从u换到v仅需简单的模加减
hs[u] = (M+hs[u]-hs[v]) % M;
hs[v] = (hs[v]+hs[u]) % M;
```

## 双`hash`(不是双重`hash`)

为避免碰撞，使用两个质数分别计算两次`hash`可有效避免碰撞(非碰撞空间是两者乘积)