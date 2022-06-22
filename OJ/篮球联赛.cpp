// http://cxsjsx.openjudge.cn/practise2022algo/03A/
// POJ 10710
// 简单的dfs，但是我垃圾死了

#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f

char comp[4][4];
int score[4], s = INF;
bool battle[6];
int bindex(int i, int j)
{
	switch (i)
	{
	case 0: return j - 1;
	case 1: return j + 1;
	case 2: return 5;
	}
}
int rk()
{
	int r = 4;
	for (int i = 1; i < 4; i++)
		if (score[i] <= score[0]) r--;
	return r;
}
void dfs(int depth, int pos)
{
	if (depth == 0)
	{
		s = min(s, rk());
		return;
	}
	for (int i = pos; i < 6; i++)
		if (battle[i])
		{
			battle[i] = false;
			int p1, p2;
			switch (i)
			{
			case 0: p1 = 0, p2 = 1; break;
			case 1: p1 = 0, p2 = 2; break;
			case 2: p1 = 0, p2 = 3; break;
			case 3: p1 = 1, p2 = 2; break;
			case 4: p1 = 1, p2 = 3; break;
			case 5: p1 = 2, p2 = 3; break;
			}
			score[p1]++;
			dfs(depth - 1, pos+1);
			score[p1]--;
			if (i > 2)
			{
				score[p2]++;
				dfs(depth - 1, pos+1);
				score[p2]--;
			}
			battle[i] = true;
		}
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		memset(score, 0, sizeof(score));
		memset(battle, 0, sizeof(battle));
		s = INF;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cin >> comp[i][j];
		int p = 0;
		for (int i = 0; i < 3; i++)
			for (int j = i + 1; j < 4; j++)
				switch (comp[i][j])
				{
				case 'L': score[j]++; break;
				case 'W': score[i]++; break;
				case '?': battle[bindex(i, j)] = true, p++; break;
				}
		dfs(p, 0);
		cout << s << endl;
	}
}
