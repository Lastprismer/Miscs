//http://cxsjsx.openjudge.cn/hw202215/B/
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAX 10002
using namespace std;
typedef long long ll;
int n, x;
int a[202] = { 0 }, b[202] = { 0 };
int dp[MAX] = {1}; // 01背包，dp[i][j]：从前i个硬币中选择，可凑成j元的数量，滚动数组优化为：直接凑成j元的数量
int ans[MAX] = { 1 }; // 去掉a[i]币值之后，硬币能不能表示价格j
int main()
{
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		for (int j = x; j >= a[i]; j--) // 背包的空间优化要从最大值开始遍历
			//dp[i][j] = dp[i - 1][j] + dp[i - 1][j - a[i]];
			dp[j] += dp[j - a[i]];
	int num = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= x; j++)
		{
			if (j < a[i])
				ans[j] = dp[j]; // 要的钱数小于面值，肯定不带自己
			else
				ans[j] = dp[j] - ans[j - a[i]];
			//dp[j]表示可以凑成j面值的方法数（包括a[i]也可以不包括a[i]），ans[j-a[i]]表示不带a[i]可以凑成j-a[i] 的方法总数，两者相减就是不带上a[i]凑成j面值的方法数。
		}

		if (!ans[x])
			b[num++] = a[i];
	}
	cout << num << endl;
	if (!num) return 0;
	cout << b[0];
	for (int i = 1; i < num; i++)
		cout << ' ' << b[i];

}
