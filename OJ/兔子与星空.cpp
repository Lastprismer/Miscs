// POJ 5442
// http://dsa.openjudge.cn/2022dsachapter7/2/
// 手撸kruskal，然后一遍过了草
#include <cstdio>
#include <list>
#include <queue>
#define MAX 100005
#define UNVISITED 0
#define VISITED 1

using namespace std;
struct EdgeNode {
	int to, weight;
	EdgeNode() :to(-1), weight(0) {}
	EdgeNode(int  _to, int _weight) :to(_to), weight(_weight) {}
};
struct Edge {
	int from, to, weight;
	Edge() :from(-1), to(-1), weight(0) {}
	Edge(int _from, int  _to, int _weight) :from(_from), to(_to), weight(_weight) {}
	bool operator >(Edge edge) const { return weight > edge.weight; }
};
class DSU
{
private:
	int* p;
	int* r;
	int size;
public:
	int equalnum;
	DSU() :p(nullptr), r(nullptr), size(0), equalnum(0) {}
	DSU(int _size) : size(_size), equalnum(_size)
	{
		p = new int[size];
		r = new int[size];
		for (int i = 0; i < size; i++)
			p[i] = i, r[i] = 1;
	}
	~DSU() { delete[] p; delete[] r; }
	int find(int x)
	{
		return p[x] == x ? x : (p[x] = find(p[x]));
	}
	void unite(int x, int y)
	{
		x = find(x), y = find(y);
		if (x == y) return;
		if (r[x] <= r[y])
			p[x] = y, r[y] += r[x];
		else p[y] = x, r[x] += r[y];
	}
};
class Graph {
private:
	int* indegree;
	list<EdgeNode>* edge_linklist;

public:
	int vertex_num;
	int edge_num;
	Graph(int __vertex_num) : vertex_num(__vertex_num), edge_num(0)
	{
		indegree = new int[vertex_num];
		for (int i = 0; i < vertex_num; i++)
			indegree[i] = 0;
		edge_linklist = new list<EdgeNode>[vertex_num];
	}
	~Graph()
	{
		delete[] edge_linklist;
		delete[] indegree;
	}
	void add_edge(int from, EdgeNode edge)
	{
		edge_linklist[from].push_back(edge);
		++edge_num;
		++indegree[edge.to];
	}
	int kruskal()
	{
		int result = 0;
		DSU dsu(vertex_num);
		priority_queue<Edge, vector<Edge>, greater<Edge>> min_heap;
		for (int i = 0; i < vertex_num; i++)
			for (auto it = edge_linklist[i].begin(); it != edge_linklist[i].end(); it++)
				min_heap.push(Edge(i, it->to, it->weight));

		while (dsu.equalnum > 1)
		{
			Edge e = min_heap.top();
			min_heap.pop();
			int from = e.from, to = e.to;
			if (dsu.find(from) != dsu.find(to))
			{
				dsu.unite(from, to);
				result += e.weight;
				dsu.equalnum--;
			}
		}
		return result;
	}
};
int main()
{
	int n;
	(void)scanf("%d\n", &n);
	Graph graph(n);
	for (int i = 0; i < n - 1; i++)
	{
		char v, v_lnk;
		int en, ev;
		(void)scanf("%c %d", &v, &en);
		for (int j = 0; j < en; j++)
		{
			(void)scanf(" %c %d", &v_lnk, &ev);
			graph.add_edge(v - 'A', EdgeNode(v_lnk - 'A', ev));
		}
		(void)getchar();
	}
	int ans = graph.kruskal();
	printf("%d", ans);
	return 0;
}
