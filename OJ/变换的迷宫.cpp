// http://cxsjsx.openjudge.cn/practise2022algo/03I/
// POJ 10718
// 经典记忆bfs，我也不知道为什么要搞过来（
// 尝试状压失败，开摆
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 101

int r, c, k, dir[4][2] = { 0,1,0,-1,1,0,-1,0 };
char map[MAX][MAX];
bool vis[MAX][MAX][10];
struct node
{
	int x, y, t;
	node(int _x, int _y, int _t) :x(_x), y(_y), t(_t) {}
};
inline bool ava(int x, int y, int t)
{
	return !vis[x][y][t] && x >= 0 && x < r && y >= 0 && y < c && (map[x][y] != '#' || (map[x][y] == '#' && !t));
}
queue<node> q;
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> r >> c >> k;
		int sx = 0, sy = 0;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 'S')
					sx = i, sy = j;
			}
		queue<node> nil;
		swap(nil, q);
		memset(vis, 0, sizeof(vis));
		q.push(node(sx, sy, 0));
		vis[sx][sy][0] = true;

		while (!q.empty()) // bfs
		{
			node p = q.front();
			if (map[p.x][p.y] == 'E')
			{
				cout << p.t << endl;
				break;
			}
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int cx = p.x + dir[i][0], cy = p.y + dir[i][1], ct = p.t + 1;
				if (!ava(cx, cy, ct%k)) continue;
				q.push(node(cx, cy, ct));
				vis[cx][cy][ct%k] = true;
			}
		}
		if (q.empty())
			cout << "Oop!" << endl;
	}
}
