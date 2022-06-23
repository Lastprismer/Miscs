// http://cxsjsx.openjudge.cn/practise2022algo/03F/
// 10715
// 奇怪的dfs
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 730

int n, a[6];

bool dfs(int p[], int num) // 用p数组中的num个数算42
{
	if (num == 1) return p[0] == 42;
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = i + 1; j < num; j++) // 枚举两个数的组合
		{
			int k[5], m = 0;
			for (int l = 0; l < num; l++)
				if (l != i && l != j)
					k[m++] = p[l]; // 数组中填入剩下的数
			k[m] = p[i] + p[j]; if (dfs(k, m + 1)) return true;
			k[m] = p[i] - p[j]; if (dfs(k, m + 1)) return true;
			k[m] = p[j] - p[i]; if (dfs(k, m + 1)) return true;
			k[m] = p[i] * p[j]; if (dfs(k, m + 1)) return true;
			if (p[i]) { k[m] = p[j] / p[i]; if (dfs(k, m + 1)) return true; }
			if (p[j]) { k[m] = p[i] / p[j]; if (dfs(k, m + 1)) return true; }
		}
	}
	return false;
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	if (dfs(a, n)) cout << "YES";
	else cout << "NO";
}
