# `hash`

考虑到情况多变，该库不封装`hash`库，下面给出常用技巧

## 常用质数

```cpp
131
257
7681
65599
786433
1145141
19260817
1e9+7/9
```

## 串`hash`

针对连续有序对象的`hash`。另外当 $B=1$ 时为集合`hash`

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

## `hash`相关

+ $M$：取模应当配合 $B$ 的取值，其实双hash情况下自然溢出就好
+ `custom_hash`：快速且难卡的`hash`

    ```cpp
    struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }
    };
    ```