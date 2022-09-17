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





**补充题2**

把下列命题符号化，并求前束范式：“有些乌龟比有些兔子跑得快”。

  令 $F(x)$：$x$ 是乌龟，$G(x)$：$x$ 是兔子，$H(x,y)$：$x$ 比 $y$ 跑得快

  命题符号化为：$\exist x \exist y(F(x) \wedge G(y) \wedge H(x,y))$



**补充题3**

给出一个解释，使下式左端为假，右端为真：
$$
\forall x(A(x) \rightarrow B(x)) \Rightarrow \exist xA(x)\rightarrow \exist xB(x)。
$$
  设有解释 $I$ 为：

1. 个体域为 $D = $ 实数域 $R$；

2. $A(x)$：$x$ 是实数；$B(x)$：$x$ 是整数

   此时左端为假，右端为真。





**1.3** 确定下列的包含和属于关系是否正确

正确：$(1)\ (4)\ (5)\ (6)\ (8)\ (9)$

错误：$(2)\ (3)\ (7)\ (10)\ (11)$



**1.10** 设 $A=\{a\}，判断下列的包含与属于关系是否正确$

$P(A)=\{\varnothing, \{a\}\}, PP(A)=\{\varnothing, \{\varnothing\}, \{\{a\}\}, \{\varnothing, \{a\}\}\}$

正确：$(1)\ (2)\ (4)\ (5)$

错误：$(2)\ (3)\ (6)$



**1.16** 化简下列集合：

$(1)=\{\{ 3 \}, \{4\}, 3,4 \}$

$(2)\ P(\varnothing)=\{\varnothing\},PP(\varnothing)=\{ \varnothing, \{\varnothing\} \}, PPP(\varnothing)=\{\varnothing, \{\varnothing\}, \{ \varnothing, \{\varnothing\} \}\},\ \therefore (2)=\varnothing$

$(3)\ P\{\varnothing\}=PP(\varnothing),\ \therefore (3)=\{\varnothing, \{\varnothing\}\}$ 



**1.13** 设 $A,B,C$ 为任意三个集合：

1. 证明 $(A-B)-C \subseteq A-(B-C)$

   左 $=(A-B)-C \subseteq A-B$

   右 $=A-(B-C) = A \cap \sim (B-C) = A \cap \sim (B \cap \sim C)=A \cap (\sim B \cup C) = (A \cap \sim B) \cup (A \cap C)$

   $=(A-B)\cup (A \cap C) \supseteq A-B$

   $\therefore (A - B)-C \subseteq A-(B-C)$

   

2. 在什么条件下，1. 中等号成立？

   结论：$A \cap C = \varnothing$ 是等号成立的充要条件。

   

   充分性：由证明过程可知：$(A-B)-C \subseteq A-B \subseteq A-(B-C)$

   $\therefore (A - B \subseteq \sim C) $ 时等号成立。

   对该式进行化简：设全集为 $E, x \in E$（过程稍简略）

   已知 $B\cap C = \varnothing \Leftrightarrow x \notin B \wedge x \in C  = 0 )$

   $(A-B \subseteq \sim C) \Leftrightarrow (x \in (A \cap \sim B) \rightarrow x \notin C = 1) \Leftrightarrow (x \in A \wedge x \notin B \wedge x \in C = 0)$

   $\therefore \text{化为析取式，用归结法得 }x \notin A \vee x \notin C = 1$

   $\therefore A \cap C = \varnothing$.

   

   必要性：$(A-B)-C = (A-B) \cap \sim C = A \cap \sim (B \cup C) = (A-B)\cap (A-C)$

   原始式子化为：$(A - B) \cap (A - C) = (A - B) \cup (A \cap C), \text{ 此时 } A - C = A, A \cap C = \varnothing$，必要性得证。

   

**1.14** 设 $A,B,C$ 为任意的集合，已知 $A \cap B = A \cap C$ 且 $\sim A \cap B = \sim A \cap C$，证明 $B=C$
$$
\begin{align}
B & = E \cap B = (A \cup \sim A) \cap B = (A \cap B) \cup (\sim A \cap B) \\
& =(A \cap C) \cup (\sim A \cap C) = (A \cup \sim A) \cap C = E \cap C = C
\end{align}
$$

**1.20** 设 $A,B,C$ 为三个集合，已知 $(A \cap C) \subseteq (B \cap C),\ (A \cap \sim C) \subseteq (B \cap \sim C)$，证明 $A \subseteq B$
$$
\begin{align}
A & = A \cap E = A \cap (C \cup \sim C) = (A \cap C) \cup (A \cap \sim C) \\
& \subseteq (B \cap C) \cup (B \cap \sim C) = B \cap (C \cup \sim C) = B
\end{align}
$$
