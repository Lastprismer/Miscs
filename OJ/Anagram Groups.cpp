// http://dsa.openjudge.cn/2022dsachapter4/3/
// POJ 1410
// 这tm考的是字符串？

#include <string> 
#include <cstring>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <iterator>
#include <vector>
using namespace std;

typedef multiset<string> StringSet;						// 存储排序后相同的字符串
typedef map<string, StringSet> String_StringSet_Map;	// 键值为排序后的字符串；将所有排序后相同的字符串全部存进对应的Multiset中，如 SSsM[aet] = {ate, eat}
struct comp
{
	bool operator ()(const pair<int, string>& c1, const pair<int, string>& c2) const
	{
		if (c1.first != c2.first)
			return c1.first > c2.first;
		return c1.second < c2.second;
	}
};
typedef map<pair<int, string>, string, comp> IntString_String_Map;	// 存储排好序的字符串和同种字符串的数量，先排数量再排字符串

String_StringSet_Map Main_Map;
IntString_String_Map Length_of_Sorted_Strings;
vector<string> temp;

int main()
{
	string s;
	while (cin >> s)
	{
		string key = s;
		sort(key.begin(), key.end());
		Main_Map[key].insert(s);
	}

	for (String_StringSet_Map::iterator it = Main_Map.begin(); it != Main_Map.end(); ++it)	// 只用对排了序之后的字符串再比较大小就行了
	{
		pair<int, string> p(it->second.size(), *(it->second.begin()));
		Length_of_Sorted_Strings[p] = it->first;
	}

	int i = 0;
	for (IntString_String_Map::iterator it = Length_of_Sorted_Strings.begin(); it != Length_of_Sorted_Strings.end(); ++it)
	{
		if (i++ >= 5)
			return 0;
		cout << "Group of size " << it->first.first << ": ";

		unique_copy(Main_Map[it->second].begin(), Main_Map[it->second].end(), ostream_iterator<string>{cout, " "});		// 输出到流
		cout << "." << endl;
	}
	return 0;
}
