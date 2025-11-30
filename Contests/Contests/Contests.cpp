#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <unordered_map>

struct pos
{
	int a = -1;
	int b = -1;
};

#define ll long long
int bfs()
{
	int a, b, n;
	std::cin >> a >> b >> n;
	pos t{ -1,-1 };
	std::queue<pos>q;
	std::unordered_map<pos, pos>m;
	q.push({ 0,0 });
	while (!q.empty())
	{
		auto it = q.front();
		q.pop();
		if (it.a == n || it.b == n)
			break;

		{
			if (it.a != a && (m[{a, it.b}].a == -1 && m[{a, it.b}].b == -1))
			{
				q.push({ a,it.b });
				m[{a, it.b}] = it;
			}
			if (it.b != b && (m[{it.a, b}].a == -1 && m[{it.a, b}].b == -1))
			{
				q.push({ it.a,b });
				m[{it.a, b}] = it;
			}
			if (it.a != 0 && (m[{0, it.a}].a == -1))
			{
				q.push({ 0,it.b });
				m[{0, it.b}] = it;
			}
			if (it.b != 0 && (m[{it.a, b}].a == -1 && m[{it.a, b}].b == -1))
			{
				q.push({ it.a,0 });
				m[{it.a, 0}] = it;
			}

			if (it.a != 0 && it.b != b)
			{
				int at = 0, bt = it.a + it.b;
				if (bt > b)
				{
					at = bt - b;
					bt = b;
				}
				if (m[{at, bt}].a == -1)
				{
					q.push({ at,bt });
					m[{at, bt}] = it;
				}
			}
			if (it.a != a && it.b != 0)
			{
				int at = it.a + it.b, bt = 0;
				if (at > a)
				{
					bt = at - a;
					at = a;
				}
				if (m[{at, bt}].a == -1)
				{
					q.push({ at,bt });
					m[{at, bt}] = it;
				}
			}
		}
	}

}


int main()
{
	bfs();
	return 0;
}