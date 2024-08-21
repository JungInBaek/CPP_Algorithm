#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Windows.h"

using namespace std;
using uint64 = unsigned __int64;


int solution(vector<string> friends, vector<string> gifts) {
	map<string, map<string, int>> breakdown;
	for (int i = 0; i < friends.size(); i++)
	{
		for (int j = 0; j < friends.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			breakdown[friends[i]].insert(pair<string, int>(friends[j], 0));
		}
	}

	map<string, int> point;
	for (string& gift : gifts)
	{
		char c_gift[25];
		strcpy_s(c_gift, gift.c_str());

		string sender;
		string recipient;
		
		int i = 0;
		while (true)
		{
			if (c_gift[i] == ' ')
			{
				sender = string(&c_gift[0], i);
				recipient = string(&c_gift[i + 1], gift.length() - (i + 1));
				break;
			}
			++i;
		}

		breakdown[sender][recipient] += 1;
		point[sender] += 1;
		point[recipient] -= 1;
	}

	int answer = 0;
	for (string& name : friends)
	{
		int count = 0;
		for (string& recipient : friends)
		{
			if (name == recipient)
			{
				continue;
			}

			if (breakdown[name][recipient] > breakdown[recipient][name])
			{
				++count;
				continue;
			}

			if (breakdown[name][recipient] != breakdown[recipient][name])
			{
				continue;
			}

			if (point[name] <= point[recipient])
			{
				continue;
			}

			++count;
		}

		answer = max(answer, count);
	}
    return answer;
}

int main()
{
	vector<string> friends = { "muzi", "ryan", "frodo", "neo" };
	vector<string> gifts = { "muzi frodo", "muzi frodo", "ryan muzi", "ryan muzi", "ryan muzi", "frodo muzi", "frodo ryan", "neo muzi" };
	int answer = solution(friends, gifts);
	cout << answer << endl;
}