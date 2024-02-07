## 差分约束

跑完最短路后，一定有`dis[v]<=dis[u]+cst(u, v)`，由此可扩展得

|形式|连边|
|:-:|:-|
|$v-u\le c$|`add(u, {v, c})`|
|$u-v\ge c$|`add(u, {v, -c})`|
|$u=v$|`add(u, {v,0}),add(v, {u,0})`|