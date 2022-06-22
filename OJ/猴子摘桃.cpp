// http://cxsjsx.openjudge.cn/practise2022algo/03D/
// POJ 10713
// 前缀和，区间和
#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAX 101

int honey;
int tree[MAX], wasp[MAX];
int treee[MAX][MAX], waspp[MAX][MAX];

int main()
{
	while (cin >> honey, honey >= 0)
	{
		int a = 0, b = 0, i;
		for (i = 1;; i++)
		{
			cin >> a >> b;
			if (a < 0 && b < 0) break;
			tree[i] = a + tree[i - 1], wasp[i] = b + wasp[i - 1]; // 前缀和
		}
		for (int k = 1; k <= i; k++)
			for (int j = 1; j <= i; j++) // 区间和
			{
				treee[k][j] = tree[j] - tree[k - 1];
				waspp[k][j] = wasp[j] - wasp[k - 1];
			}
		int ans = 0;
		for (int k = 1; k <= i; k++)
			for (int j = 1; j <= i; j++)
				if (waspp[k][j] <= honey) ans = max(ans, treee[k][j]); // 就很简单了
		cout << ans << endl;

	}
}
