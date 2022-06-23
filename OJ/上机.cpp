// http://cxsjsx.openjudge.cn/practise2022algo/03G/
// POJ 10716
// 思路很神奇的dp：过程怎么样不重要，要的是最终结果
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 10002
int n, a[MAX], b[MAX], c[MAX];
// int dp[MAX][4]; // 0：两边都没放；1：左边已放；2：右边已放下；3：左右都放
// 不通过放人个数来看，而是看各个座位坐下时左右的情况——最后一定是满的，两种方法得到的结果相同
int dp[2][4]; //滚动数组优化

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	dp[1][0] = a[1], dp[1][1] = -INF; // 左边不可能放
	dp[1][2] = b[1], dp[1][3] = -INF;
	for (int i = 2; i <= n; i++)
	{
		int leftnull = max(dp[(i - 1) % 2][2], dp[(i - 1) % 2][3]), leftoccupied = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1]);
		dp[i % 2][0] = leftnull + a[i];
		// 栗子：放i时两边没放，则左边没放，放i-1号的时候右边已经放下了，所以是2或者3
		dp[i % 2][1] = leftoccupied + b[i];
		dp[i % 2][2] = leftnull + b[i];
		dp[i % 2][3] = leftoccupied + c[i];
	}
	cout << max(dp[n % 2][0], dp[n % 2][1]);

}
