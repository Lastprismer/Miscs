// http://dsa.openjudge.cn/2022dsachapter3/2/
// 7206
// bfs复健捏
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#define MAX 1000000

using namespace std;
bool map[11][11] = { 0 };
int visited[11][11] = { 0 };
int path[11][11] = { 0 };
int dir[8][2] = { 1,2,-1,2,1,-2,-1,-2,2,1,-2,1,2,-1,-2,-1 };
typedef struct point
{
	int x;
	int y;
	int depth;
	point() :x(0), y(0), depth(0) {}
	point(int _x, int _y, int _dep) :x(_x), y(_y), depth(_dep) {};
};
inline bool valid_move(point beg, point des)
{
	if (des.x < 0 || des.x > 10 || des.y < 0 || des.y > 10) return false;
	int dx = des.x - beg.x, dy = des.y - beg.y;
	if (abs(dx) == 2)
	{
		int s = dx > 0 ? 1 : -1;
		int nx = beg.x + s;
		return !map[nx][beg.y] && !visited[nx][beg.y];
	}
	int s = dy > 0 ? 1 : -1;
	int ny = beg.y + s;
	return !map[beg.x][ny] && !visited[beg.x][ny];
}
inline point decode_path(int i)
{
	return point(i / 100, i % 100, -1);
}
int main()
{
	int m, p, q;
	point b, e;
	cin >> b.x >> b.y >> e.x >> e.y;

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> p >> q;
		map[p][q] = true;
	}

	deque<point> que;
	que.push_back(b);
	visited[b.x][b.y] = true;
	int step_count = 0; // 0则没有结果，>0则为最小结果的步数
	int step_num = 0; // 最小结果的总数

	while (!que.empty())
	{
		point back = que.back();
		que.pop_back();
		for (int i = 0; i < 8; i++)
		{
			if (step_count && back.depth >= step_count)
				break; // 步数过长，剪枝
			int xx = back.x + dir[i][0], yy = back.y + dir[i][1];
			point temp(xx, yy, back.depth + 1);
			if (valid_move(back, temp))
			{
				path[xx][yy] = back.x * 100 + back.y;
				if (temp.x == e.x && temp.y == e.y)
				{
					if (!step_count || temp.depth < step_count)
					{
						step_count = temp.depth;
						step_num = 1;
						break; // 本n层已经有一个到了，剩下的就不会到了；由本层扩展出的到达终点的步数一定>=n+1，同样剪枝剪掉
					}
					else if (temp.depth == step_count)
						step_num++;
				}
				que.push_front(temp);
				visited[xx][yy] = true;
			}
		}
	}

	if (step_num > 1)
	{
		cout << step_count;
		return 0;
	}
	stack<point>ans;
	int i = e.x, j = e.y;
	ans.push(e);
	while (path[i][j] != b.x * 100 + b.y)
	{
		point tmp = decode_path(path[i][j]);
		ans.push(tmp);
		i = tmp.x, j = tmp.y;
	}
	cout << "(" << b.x << "," << b.y << ")";
	while (!ans.empty())
	{
		point p = ans.top();
		ans.pop();
		cout << "-(" << p.x << "," << p.y << ")";
	}
}
