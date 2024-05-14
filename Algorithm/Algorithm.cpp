#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;


static void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
	};
	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	bool connected = false;
	for (vector<Vertex*>::iterator it = v[0].edges.begin(); it != v[0].edges.end(); ++it)
	{
		if (*it == &v[3])
		{
			connected = true;
			break;
		}
	}
}

static void CreateGraph_2()
{
	struct Vertex {};
	vector<Vertex> v;
	v.resize(6);

	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	vector<int>& adj = adjacent[0];
	bool connected = std::find(adj.begin(), adj.end(), 3) != adj.end();
}

static void CreateGraph_3()
{
	struct Vertex {};
	vector<Vertex> v;
	v.resize(6);

	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	bool connected = adjacent[0][3];

	// 가중치 그래프
	vector<vector<int>> adjacent2(6, vector<int>(6, -1));
	adjacent2[0][1] = 15;
	adjacent2[0][3] = 35;
	adjacent2[1][0] = 15;
	adjacent2[1][2] = 5;
	adjacent2[1][3] = 10;
	adjacent2[3][4] = 5;
	adjacent2[5][4] = 5;

	bool connected2 = adjacent2[0][3] != -1;
	int weight = adjacent2[0][3];
}

int main()
{
	CreateGraph_1();
	CreateGraph_2();
	CreateGraph_3();
}