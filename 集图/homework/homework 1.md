**补充题1 用真值表证明德摩根律**
$$
\neg(p \wedge q) \Leftrightarrow \neg p \vee \neg q \\
\neg(p \vee q) \Leftrightarrow \neg p \wedge \neg q
$$
真值表：
| $p$  | $q$  | $\neg(p \wedge q)$ | $\neg p \vee \neg q$ |
| :--: | :--: | :----------------: | :------------------: |
|  0   |  0   |         1          |          1           |
|  0   |  1   |         1          |          1           |
|  1   |  0   |         1          |          1           |
|  1   |  1   |         0          |          0           |

| $p$  | $q$  | $\neg(p \vee q)$ | $\neg p \wedge \neg q$ |
| :--: | :--: | :--------------: | :--------------------: |
|  0   |  0   |        1         |           1            |
|  0   |  1   |        0         |           0            |
|  1   |  0   |        0         |           0            |
|  1   |  1   |        0         |           0            |

$$
\therefore \neg(p \wedge q) \Leftrightarrow \neg p \vee \neg q, \\
 \neg(p \vee q) \Leftrightarrow \neg p \wedge \neg q.
$$

