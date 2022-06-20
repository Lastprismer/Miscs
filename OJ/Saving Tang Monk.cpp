// http://cxsjsx.openjudge.cn/hw202217/A/
// POJ 10956
// 状压，备忘录bfs
#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 102
#define SNAKE_INDEX 30
#define SNKILL (1<<6)-1

struct node
{
	int x, y, cost, key, snakeKill;
	node() = default;
	node(int _x, int _y, int c, int k, int snk) :x(_x), y(_y), cost(c), key(k), snakeKill(snk) {}
	bool operator <(const node& a) const { return cost > a.cost; }
};

int m, n;
int dir[4][2] = { 0,1,0,-1,1,0,-1,0 };
int mapp[MAX][MAX];
bool dp[MAX][MAX][11][SNKILL + 1]; //在(i1,i2)处，有i3个钥匙，蛇的状态是i4，是否走过
node start;
inline bool canMove(int i, int j, int key, int snk) { return i >= 1 && i <= n && j >= 1 && j <= n && mapp[i][j] != -1 && !dp[i][j][key][snk]; }
inline bool snakeAlive(int digit, int index) { return ((digit >> (index - 1)) & 1) == 0; } // 蛇：00000初始，00100三号蛇被杀
bool input()
{
	cin >> n >> m;
	if (!n && !m) return false;
	memset(mapp, -1, sizeof(mapp));
	memset(dp, 0, sizeof(dp));
	int s = SNAKE_INDEX;
	cin.get();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char c = cin.get();
			switch (c)
			{
			case 'K': start.x = i, start.y = j, mapp[i][j] = 0; break; // 起点
			case 'T': mapp[i][j] = m + 1; break; // 终点
			case 'S': mapp[i][j] = ++s; break;	// 第几条蛇
			case '#': break; // 默认-1走不了
			case '.': mapp[i][j] = 0; break;
			default: mapp[i][j] = c - '0'; break;
			}
		}
		cin.get();
	}
	return true;
}
int bfs()
{
	priority_queue<node> path;
	path.push(start);
	dp[1][1][0][0] = true;
	while (!path.empty())
	{
		node cur = path.top();
		path.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			int nkey = cur.key;
			int nsnk = cur.snakeKill;
			if (!canMove(nx, ny, nkey, nsnk)) continue;
			if (mapp[nx][ny] == m + 1 && nkey == m) // 找到
				return cur.cost + 1;
			else if (mapp[nx][ny] == 0 || mapp[nx][ny] == m + 1) // 视作空地
			{
				dp[nx][ny][nkey][nsnk] = true;
				path.push(node(nx, ny, cur.cost + 1, nkey, nsnk));
			}
			else if (mapp[nx][ny] > SNAKE_INDEX) // 蛇
			{
				int index = mapp[nx][ny] - SNAKE_INDEX;
				if (!snakeAlive(nsnk, index)) // 杀蛇
				{
					dp[nx][ny][nkey][nsnk] = true;
					path.push(node(nx, ny, cur.cost + 1, nkey, nsnk));
				}
				else
				{
					nsnk |= 1 << (index - 1);
					path.push(node(nx, ny, cur.cost + 2, nkey, nsnk)); // 不可能杀了蛇不走
				}
			}
			else // 钥匙
			{
				if (mapp[nx][ny] == nkey + 1) // 正确的
				{
					dp[nx][ny][nkey][nsnk] = true;
					path.push(node(nx, ny, cur.cost + 1, nkey + 1, nsnk));
				}
				else // 孬的
				{

					dp[nx][ny][nkey][nsnk] = true;
					path.push(node(nx, ny, cur.cost + 1, nkey, nsnk));
				}

			}
		}
	}
	return -1;
}
int main()
{
	while (input())
	{
		int p = bfs();
		if (p >= 0) cout << p << endl;
		else cout << "impossible" << endl;
	}
}
