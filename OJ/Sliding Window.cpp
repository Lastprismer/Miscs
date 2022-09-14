// http://dsa.openjudge.cn/2022dsachapter3/1/
// 3866
// 单调队列：解决 在长度为L的区间内，查找最大/最小值；时间复杂度最快，为O(n)
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>

#define MAX 1000000
using namespace std;

int a[MAX] = { 0 };
int n, k;
deque<int>q; // 存下标
/*
单调队列
*/
int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
		
	for (int i = 0; i < n; i++)
	{
		while (!q.empty() && a[q.front()] > a[i]) q.pop_front(); // 维持队列单调性
		q.push_front(i);
		if (i >= k - 1)
		{
			while (!q.empty() && q.back() < i - k + 1) q.pop_back(); // 离开区间
			printf("%d ",a[q.back()]);
		}
	}
	cout << endl;
	q.clear();
	for (int i = 0; i < n; i++)
	{
		while (!q.empty() && a[q.front()] < a[i]) q.pop_front(); // 维持队列单调性
		q.push_front(i);
		if (i >= k - 1)
		{
			while (!q.empty() && q.back() < i - k + 1) q.pop_back(); // 离开区间
			printf("%d ", a[q.back()]);
		}
	}

}
