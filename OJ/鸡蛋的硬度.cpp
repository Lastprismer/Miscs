// http://cxsjsx.openjudge.cn/practise2022algo/02G/
// POJ 7627
// dp，但是研究了2个蛋的情况（可手解，多个蛋是不是同样的多项式结构？不知道）
#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 1001

int dp[101][11]; // dp[i][j]表示i层楼有j个蛋所需的最少次数
int n, m;
/*
* 1个蛋i层楼，扔i次，dp[i][1] = i
* 2个蛋i层楼。假设第一次鸡蛋从x层丢下：
* 碎了，第二个为dp[x-1][1] = x-1；
* 没碎，相当于x层就是0层，变为dp[n-x][2]（x层以上的n层以下的测试次数和0到n-x一样
* 最少需要max(x-1, dp[n-x][2])次。
* ////   dp[n][2]=min{ 1+max(i-1, dp[n-i][2]) }, i=1,2...n（这一条足够了，后面的是人力快速解法）
* 如果第一次扔得很高，那最少次数就是x；后面某一次扔的高碎了，那差距很大的区间会使次数增加，孬
* 思路：区间平分（找dp[n-i][2]<=i-1）：设已知最少是a次，当dp[n-a][2]<=a-1，让他取a-1，第二次就是从a到a+(a-1)层，第三次a+(a-1)+(a-2)……符合题意，如此构造最小为a+...+2+1 = a(a+1)/2，方程a(a+1)/2 > n即可
* （第一次不在a层丢也能如此构造（在a-k层，然后解，下一个阶梯最大是a-k+(a-1)且最后累加能到n），但你得先把a求出来
* 
* 推广到n层楼，m个蛋
* 丢一个，碎了，dp[n-1][m-1]
* 没碎，dp[n-i][m]，遍历i
*/
int f(int n, int m)
{
	if (dp[n][m] < INF)
		return dp[n][m];
	for (int i = 1; i <= n; i++)
		dp[n][m] = min(dp[n][m], 1 + max(f(i - 1, m - 1), f(n - i, m)));
	return dp[n][m];
}
int main()
{
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i < 101; i++) dp[i][1] = i, dp[i][0] = 0;
	for (int i = 0; i < 11; i++) dp[1][i] = 1, dp[0][i] = 0;
	while (cin >> n >> m)
	{
		cout << f(n,m) << endl;
	}
}
