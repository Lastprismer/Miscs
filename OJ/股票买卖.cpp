// http://cxsjsx.openjudge.cn/practise2022algo/01I/
// POJ 8464
// 枚举？他们都说是dp，但是很怪，不难
#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
#define INF 0x3f3f3f3f
#define PI acos(-1)

#define MAX 100001

int w[MAX] = { 0 }, sell[MAX]= {0}, buy[MAX]={0}; // 卖出赚的最多和买入赚的最多
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> w[i];
		memset(sell, 0, sizeof(sell));
		memset(buy, 0, sizeof(buy));
		int m = INF;
		for (int i = 0; i < n; i++)
			m = min(m, w[i]), sell[i] = w[i] - m; // 第i天卖最多能赚的钱（第几天买进去的不知道）
		m = -INF;
		for (int i = n - 1; i >= 0; i--)
			m = max(m, w[i]), buy[i] = m - w[i]; // 第i天买最多能赚的钱（第几天卖出去没有存）
		int l = -INF;
		m = l;
		for (int i = 0; i < n; i++)
		{
			m = max(m, sell[i]); // 前i天能卖出的最大利益
			l = max(l, m + buy[i]); // 两次买入卖出的最高价格，为前些天卖出的最高获利+这天买入的最高获利
		}
		cout << l << endl;
	}
}
