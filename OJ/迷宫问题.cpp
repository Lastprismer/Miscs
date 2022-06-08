// http://cxsjsx.openjudge.cn/hw202216/A/
// 基础的bfs
// POJ 7084
#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<deque>
using namespace std;
int a[5][5] = { 0 }, path[5][5] = { 0 }, dir[4][2] = { {0,1},{0,-1},{1,0}, {-1,0} }, ans[25] = { 0 };
struct point
{
	int x, y;
	point(int a, int b) :x(a), y(b) {}
};
deque<point> que;
inline bool valid(int x, int y)
{
	return (x < 5 && x >= 0 && y < 5 && y >= 0) && a[x][y] == 0 && path[x][y] == -1;
}
int main()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			scanf("%d", &a[i][j]);
			path[i][j] = -1;
		}
	path[0][0] = 0;
	que.push_back(point(0, 0));
	while (!que.empty())
	{
		point temp = que.back();
		que.pop_back();
		for (int i = 0; i < 4; i++)
		{
			int xx = temp.x + dir[i][0], yy = temp.y + dir[i][1];
			if (valid(xx, yy))
			{
				que.push_front(point(xx, yy));
				path[xx][yy] = temp.x * 10 + temp.y;
			}
		}
	}

	int front = path[4][4], num = 0;
	while (front != 0)
	{
		int xx = front / 10, yy = front % 10;
		ans[num++] = front;
		front = path[xx][yy];
	}
	printf("(0,0)\n");
	while (num-- > 0)
		printf("(%d,%d)\n", ans[num] / 10, ans[num] % 10);
	printf("(4,4)");
	return 0;
}
