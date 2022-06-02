//http://cxsjsx.openjudge.cn/hw202215/A/
#include<iostream>
#include<cstring>
#define MAX 251
using namespace std;
typedef long long ll;
ll dp[MAX][MAX];
/*
1: (1)
2: (1 1), (2)
3: (1 1 1), (3),
4: (1 1 1 1), (1 2 1), (2 2), (4)
5: (1 1 1 1 1), (1 3 1), (5)
6: (1 1 1 1 1 1), (1 1 2 1 1), (1 2 2 1), (1 4 1), (2 2 2), (3 3), (6)
7: (1 1 1 1 1 1 1), (1 1 3 1 1), (1 5 1), (2 3 2), (7)
8: (1 1 1 1 1 1 1 1), (1 1 1 2 1 1 1), (1 1 2 2 1 1), (1 2 2 2 1), (1 3 3 1), (1 1 4 1 1), (1 6 1), (2 2 2 2), (2 4 2), (4 4), (8)
dp[i][j]表示将i分解为最小数字为j的数量
dp[i][j]=sum(dp[i-2*j][k]), 其中i-2*j>=k>=j)
*/
int main()
{
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i < MAX; i++)
	{
		dp[i][i] = 1;
		if (i % 2 == 0)
			dp[i][i / 2] = 1;
		for (int j = 1; i - 2 * j >= j; j++)
			for (int k = j; i - 2 * j >= k; k++)
				dp[i][j] += dp[i - 2 * j][k];
	}
	int n;
	while (cin >> n)
	{
		if (!n)
			break;
		ll sum = 0;
		for (int i = 1; i <= n; i++)
			sum += dp[n][i];
		cout << n << ' ' << sum << endl;
	}
}
