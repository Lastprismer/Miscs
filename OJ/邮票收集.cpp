// http://cxsjsx.openjudge.cn/practise2022algo/04B/
// POJ 20776
// dp
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
#define MAX 1001

int n, k, a[MAX], dp[MAX]; // dp[i]：组成i的种数
int main()
{
	while (cin >> n >> k)
	{
		if (!n && !k) return 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
			cin >> a[i], dp[a[i]] = 1;

		for (int i = 1; i <= k; i++) // 钱
		{
			int p = INF;
			for (int j = 1; j <= n; j++) // 票
				if (i >= a[j])
					p = min(p, dp[i - a[j]]);
			dp[i] = p + 1;
		}
		if (dp[k] != INF + 1) cout << dp[k] << endl;
		else cout << -1 << endl;
	}
}
