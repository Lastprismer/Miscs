// http://cxsjsx.openjudge.cn/practise2022algo/04A
// 20775
// 没啥难度，枚举+unique+二分查找
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <deque>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 101
struct point
{
	int x, y;
	point(int _x, int _y) :x(_x), y(_y) {}
	point() :x(0), y(0) {}
	bool operator< (const point& b) const
	{
		return (y == b.y ? x < b.x : y < b.y);
	}
	bool operator== (const point& b)
	{
		return x == b.x && y == b.y;
	}
};
point p[50];
bool bisearch(int n, const point& m) // 查找范围：[left,right)
{
	int left = 0, right = n;
	while (left < right)
	{
		int middle = left + (right - left) / 2;
		if (p[middle] < m)
			left = middle + 1;
		else if (!(p[middle] == m))
			right = middle;
		else return true;
	}
	return false;
}
bool bisearch2(int n, const point& m) // 查找范围：[left,right]
{
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int middle = left + (right - left) / 2;
		if (p[middle] < m)
			left = middle + 1;
		else if (!(p[middle] == m))
			right = middle - 1;
		else return true;
	}
	return false;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> p[i].x >> p[i].y;
		sort(p, p + n);
		n = unique(p, p + n) - p;
		int ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) // 枚举两个点作为对角线
			{
				if (p[i].x == p[j].x || p[i].y == p[j].y) continue;
				point q(p[i].x, p[j].y), q2(p[j].x, p[i].y);
				ans += bisearch(n, q) && bisearch(n, q2);
			}
		cout << ans / 2 << endl; // 一个矩形有两个对角线
	}
}
