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

   由证明过程可知：$(A-B)-C \subseteq A-B \subseteq A-(B-C)$

   $\therefore (A - B \subseteq \sim C) \wedge (B \cap C= \varnothing) $ 时成立。

   对该式进行化简：设全集为 $E, x \in E$（过程稍简略）

   $B\cap C = \varnothing \Leftrightarrow x \notin B \wedge x \in C  = 0 )$

   $(A-B \subseteq \sim C) \Leftrightarrow (x \in (A \cap \sim B) \rightarrow x \notin C = 1) \Leftrightarrow (x \in A \wedge x \notin B \wedge x \in C = 0)$

   $\therefore \text{化为析取式，用归结法得 }x \notin A \vee x \notin C = 1$

   $\therefore (A \cap C = \varnothing) \vee (B \cap C = \varnothing)$.

   

   原始式子化为：$(A - B) \cup (A - C) = (A - B) \cup (A \cap C), \text{ 此时 } A - C = A, A \cap C = \varnothing$，必要性得证。

   

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