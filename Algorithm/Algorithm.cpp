#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		int now = _heap.size();
		_heap.push_back(data);

		while (now > 0)
		{
			int parent = (now - 1) / 2;
			if (_predicate(_heap[parent], _heap[now]))
			{
				T temp = _heap[parent];
				_heap[parent] = _heap[now];
				_heap[now] = temp;
			}
			now = parent;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();
		
		int size = _heap.size();

		int now = 0;
		while (true)
		{
			int child = (now * 2) + 1;
			if (child >= size)
			{
				break;
			}

			if (child + 1 < size && _predicate(_heap[child], _heap[child + 1]))
			{
				++child;
			}

			if (_predicate(_heap[now], _heap[child]))
			{
				T temp = _heap[now];
				_heap[now] = _heap[child];
				_heap[child] = temp;
			}

			now = child;
		}
	}

	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap;
	Predicate _predicate;
};



int main()
{
	//priority_queue<int, vector<int>, greater<int>> pq;

	PriorityQueue<int, greater<int>> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);

	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}
}