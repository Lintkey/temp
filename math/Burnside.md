设 $X$ 是状态的集合，$G$ 是定义在 $X$ 上的置换群，$\forall x\in X,g\in G\rArr g(x)\in X$

则 $X$ 在 $G$ 作用下形成的等价类数量 $|X/G|$ 满足 $\rm Burnside$ 定理：

$$
|X/G|=\dfrac{1}{|G|}\sum_{g\in G}\big|\{x|x\in X,g(x)=x\}\big|
$$

当 $X$ 包含由 $m$ 种元素构成的所有状态(不限制构成状态的单种元素个数)时，有 $\rm P\acute{o}lya$ 定理：

$$
|X/G|=\dfrac{1}{|G|}\sum_{g\in G} m^{c(g)}
$$

$c(g)$ 为置换 $g$ 的轮换数，通俗的说就是置换 $g$ 上环的数量