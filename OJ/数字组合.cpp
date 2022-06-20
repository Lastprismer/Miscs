// http://cxsjsx.openjudge.cn/practise2022algo/01J/
// POJ 2985
// 背包变形
#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 1001

int num[21], dp[1001] = { 1 }; // 初始状态；dp[i]：所有数组成i的种数
int main()
{
	int n, t;
	cin >> n >> t;
	for (int i = 0; i < n; i++)
		cin >> num[i];
	for (int i = 0; i < n; i++) // 遍历所有给了的数num[i]
		for (int j = t; j >= num[i]; j--) // j为(j-num[i])和num[i]组成
		{
			dp[j] += dp[j - num[i]];
		}
	cout << dp[t] << endl;
}
