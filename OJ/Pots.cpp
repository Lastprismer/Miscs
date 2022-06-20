// http://cxsjsx.openjudge.cn/hw202217/B/
// POJ 2152
// 普通的bfs+记忆化搜索
#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 103

struct node
{
	int cura, curb, par, depth;
	char pathi[MAX + 1];
	node(int ca, int cb, int parent, int deep) :cura(ca), curb(cb), par(parent), depth(deep) {};
};

string path[6] = { "FILL(1)", "FILL(2)","DROP(1)", "DROP(2)", "POUR(1,2)", "POUR(2,1)" };
queue<node> tree;
bool vis[MAX][MAX] = { 1 }; // 记忆化搜索
int a, b, c;

void operate(int ca, int cb, int& oa, int& ob, int index)
{
	switch (index)
	{
	case 0: oa = a, ob = cb; break;
	case 1: oa = ca, ob = b; break;
	case 2: oa = 0, ob = cb; break;
	case 3: oa = ca, ob = 0; break;
	case 4: if (ca >= b - cb) oa = ca - (b - cb), ob = b;
		  else oa = 0, ob = ca + cb; break;
	case 5: if (cb >= a - ca) oa = a, ob = cb - (a - ca);
		  else oa = ca + cb, ob = 0; break;
	}
}

void bfs()
{
	node n(0, 0, 0, 0);
	memset(n.pathi, 0, sizeof(n.pathi));
	tree.push(n);
	while (!tree.empty())
	{
		node p = tree.front();
		tree.pop();
		if (p.cura == c || p.curb == c) // 找到
		{
			cout << p.depth << endl;
			for (int i = 1; i <= p.depth; i++)
				cout << path[p.pathi[i]] << endl;
			return;
		}
		node l(p);
		l.depth++;
		for (int i = 0; i < 6; i++)
		{
			operate(p.cura, p.curb, l.cura, l.curb, i);
			if (!vis[l.cura][l.curb])
			{
				vis[l.cura][l.curb] = true;
				l.pathi[l.depth] = i;
				tree.push(l);
			}
		}
	}
	cout << "impossible" << endl;
}
int main()
{
	cin >> a >> b >> c;
	bfs();
}
