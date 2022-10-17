// http://dsa.openjudge.cn/2022dsachapter6/1
// POJ 6308
// ...
#include <iostream>
#include <string>

using namespace std;
string s;
int i, ho, hb, cnt = 0;

void dfs(int l1, int l2)
// 递归函数，碰到u就是原树子树，退出一层递归
// l1是原树深度，每次碰到d就++，碰到u就结算
// 某个点在二叉树里的深度：父节点深度+左兄弟个数+1
{
    int son = 0; // 父节点的子节点
    while (s[i] == 'd')
    {
        i++;
        dfs(l1 + 1, l2 + son + 1);
        son++; // 也就是这个节点的左兄弟
    }
    ho = ho > l1 ? ho : l1;
    hb = hb > l2 ? hb : l2;
    i++;
}

int main()
{
    while (cin >> s)
    {
        if (s[0] == '#') return;
        ho = 0;
        hb = 0
        i = 0;
        dfs(0, 0);
        cout << "Tree " << ++cnt << ": " << ho << " => " << hb << endl;
    }
    return 0;
}
