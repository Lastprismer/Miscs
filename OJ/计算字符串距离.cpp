// http://cxsjsx.openjudge.cn/practise2022algo/01H/
// POJ 2988
// 简单的dp
#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 1001

int dp[MAX][MAX]; // dp[i][j]表示第一个的前i个字符组成的串和第二个的前j个字符组成的串的距离
char a[MAX], b[MAX];

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		scanf("%s %s", a, b);
		memset(dp, 0, sizeof(dp));
		int la = strlen(a), lb = strlen(b);
		for (int i = 0; i <= la; i++) dp[i][0] = i;
		for (int j = 0; j <= lb; j++) dp[0][j] = j; // 任何字符串到空字符串的距离就是自身的长度，边界
		for (int i = 1; i <= la; i++)
			for (int j = 1; j <= lb; j++)
			{
				if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1]; // 某个字符相同，不用变
				else dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1; // 变：变一次；修改：把a[i]变为b[j]时看的是dp[i-1][j-1]
			}
		printf("%d\n", dp[la][lb]);
	}
	return 0;
}
