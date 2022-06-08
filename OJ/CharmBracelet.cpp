// http://cxsjsx.openjudge.cn/hw202215/C/
// POJ 7113
// 普通的滚动数组空间优化的01背包
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAX 3500
using namespace std;
typedef long long ll;
int n, m, w[MAX] = { 0 }, d[MAX] = { 0 };
int dp[12900] = { 0 }; //dp[i][j]：前i件中总体积不超过j的最大价值
// 空间优化：滚动数组dp[j]：可选的不超过j的最大价值
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> d[i];
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--)
			//dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + d[i]);
			if (j >= w[i])
				dp[j] = max(dp[j], dp[j - w[i]] + d[i]);
	cout << dp[m];
}
