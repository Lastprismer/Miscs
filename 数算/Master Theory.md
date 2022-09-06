# 主定理

## 公式

假设有递推关系式

$$
T(n) = aT(\frac{n}{b})+f(n)
$$

那么

![](https://github.com/Lastprismer/Miscs/blob/main/%E6%95%B0%E7%AE%97/Assets/MommyTalk1662475369768.svg)

$(*)$指代的条件：$\exist c<1,\ n_0>0,\ s.t.\forall n>n_0,\ af(\frac{n}{b})\leqslant cf(n)$

$\Theta(n^{log_ba})$为“基准函数”

**换一种写法：**

假设有递推关系式

$$
T(n) = aT(\frac{n}{b})+O(n^d)\qquad a>0,\ b>1,\ d\geqslant 0
$$

那么

$$
 T(n)=\left\{
\begin{array}{lcl}
O(n^d),    &&d>log_ba\\
O(n^dlogn),&&d=log_ba\\
O(n^{log_ba}),&&d<log_ba\\
\end{array}\right. 
$$

## 证明
证明要点：通过补全递归树，得到

$$
T(n)=\Theta(n^{log_ba})+\sum_{i=0}^{log_bn}a^if(\frac n{b^i})
$$

前一项来自时间复杂度为 $\Theta(1)$ 的最底层的加和（$n^{log_ba}\Theta(1)$），后一项是第 $i$ 层 $a^i$ 个节点乘该层 $f(\frac n{b^i})$ 单个节点时间复杂度的求和。其他的代入就好。

## 例子

*二分查找*：$T(n)=T(\frac{n}{2})+\Theta(1)$
$a=1,\ b=2,\ f(n)=\Theta(1)，\Theta(n^{log_ba})=f(n)$，适用于情况2
故复杂度为$\Theta(n^{log_ba}logn)=\Theta(logn)$

*归并排序*：$T(n)=2T(n/2)+\Theta(n)$
$a=2,\ b=2, f(n)=\Theta(1),\ \Theta(n^{log_ba})=f(n)$，适用于情况2
故复杂度为$\Theta(n^{log_ba}logn)=\Theta(nlogn)$
