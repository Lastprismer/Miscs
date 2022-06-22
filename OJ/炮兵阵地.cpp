// http://cxsjsx.openjudge.cn/practise2022algo/
// POJ187
// 究极状态压缩dp
#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 101
#define MAXM 11
#define MAXSTATE 100

int map[101];
int stateArray[65]; // 所有可行的状态（二进制数）只有60种
int num[65]; // 每一种状态含有的炮兵数目
int dp[101][65][65]; // dp[i][j][k]表示第i行上放置情况为j（序号），i-1行上为k（序号）时的最大方案数，每两行确认下一行
int n, m;
int main()
{
	// 输入
	cin >> n >> m; char c;
	for (int i = 0; cin.get(),i < n; i++)
		for (int j = 0; j < m; j++)
			if ((c = cin.get()) == 'H')
				map[i] |= 1 << j; // 1为山0为平
	
	int temp = 0;
	// 把所有可行的单行状态（单行不打）存到sA里，需要时检测调用
	for (int i = 0; i < (1 << m); i++)
	{
		if (i & (i << 1) || i & (i << 2) || i & (i >> 1) || i & (i >> 2)) continue; // eg: i&(i<<1)检测右侧1格，0为无
		int a = 0, ii;
		for (ii = i; ii > 0; ii >>= 1) a += (ii & 1) ? 1 : 0; // 检测i二进制中1的数量
		stateArray[temp] = i, num[temp++] = a;
	}

	// 每一行和前两行有关，所以前两行单独处理（也可以改下标，但懒了，且单独处理省时间
	for (int i = 0; i < temp; i++)
	{
		if (stateArray[i] & map[0]) continue; // 填充第零行
		dp[0][i][0] = num[i];
	}

	for (int i = 0; i < temp; i++) // 遍历第一行
	{
		if (stateArray[i] & map[1]) continue;
		for (int j = 0; j < temp; j++) // 查找第零行
		{
			if ((stateArray[j] & map[0]) || (stateArray[i] & stateArray[j])) continue; // 地形与交错行
			dp[1][i][j] = max(dp[1][i][j], dp[0][j][0] + num[i]); // 状态转移方程：max(当前自己,上一行状态+增长量)
		}

	}

	for (int i = 2; i < n; i++) // 第i行
		for (int j = 0; j < temp; j++) // i所有状态
		{
			if (stateArray[j] & map[i]) continue;
			for (int k = 0; k < temp; k++) // i-1所有状态
			{
				if ((stateArray[k] & map[i - 1]) || (stateArray[k] & stateArray[j])) continue;
				for (int l = 0; l < temp; l++) // i-2所有状态
				{
					if ((stateArray[l] & map[i - 2]) || (stateArray[l] & stateArray[j]) || (stateArray[l] & stateArray[k])) continue;
					dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][l] + num[j]);
				}
			}
		}

	int ans = 0;
	for (int i = 0; i < temp; i++)
		for (int j = 0; j < temp; j++)
			ans = max(ans, dp[n - 1][i][j]);
	cout << ans;
	return 0;
}
