// http://cxsjsx.openjudge.cn/hw202215/B/
// POJ 4976
// 01背包再附加一点内容
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAX 10002
using namespace std;
typedef long long ll;
int n, x;
int a[202] = { 0 }, b[202] = { 0 };
int dp[MAX] = { 1 }; // 01背包，dp[i][j]：从前i个硬币中选择，可凑成j元的数量，滚动数组优化为：直接凑成j元的数量
// ideal为欲凑成的数目，cur为检测的面值
// 如果cur为必须的，那么含有cur、凑成ideal的数目，应当等于不含有cur、凑成ideal-cur的数目
int kinds(int ideal, int cur)
{
	if (ideal < 0) return 0; // 提前return跳出递归，小优化
	return dp[ideal] - kinds(ideal - cur, cur);
}
int main()
{
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
        {                
		cin >> a[i];
		for (int j = x; j >= a[i]; j--) // 从最大值开始遍历，简单的滚动数组优化01背包
			//dp[i][j] = dp[i - 1][j] + dp[i - 1][j - a[i]];
			dp[j] += dp[j - a[i]];
        }
	int num = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!kinds(x, a[i]))
			b[num++] = a[i];
	}
	cout << num << endl;
	if (!num) return 0;
	cout << b[0];
	for (int i = 1; i < num; i++)
		cout << ' ' << b[i];
}
