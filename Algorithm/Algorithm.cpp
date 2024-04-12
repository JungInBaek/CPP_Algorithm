#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;


// Queue (FIFO First-In-First-Out 선입선출)

template<typename T>
class ArrayQueue
{
public:
	ArrayQueue()
	{
		_container.resize(100);
	}

	void push(const T& value)
	{
		// TODO: 다 찼는지 체크
		if (_size == _container.size())
		{
			// 증설
			int newSize = max(1, _size * 2);
			vector<T> newData;
			newData.resize(newSize);

			// 데이터 복사
			for (int i = 0; i < _size; i++)
			{
				newData[i] = _container[_front];
				_front = (_front + 1) % _container.size();
			}
			_container.swap(newData);
			_front = 0;
			_back = _size;
		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size();
		_size++;
	}

	void pop()
	{
		// TODO: 비었는지 체크
		if (!empty())
		{
			_front = (_front + 1) % _container.size();
			_size--;
		}
	}

	T& front()
	{
		return _container[_front];
	}

	bool empty()
	{
		return _size == 0;
	}

	int size()
	{
		return _size;
	}

private:
	vector<T> _container;
	int _front = 0;
	int _back = 0;
	int _size = 0;
};

template<typename T>
class ListQueue
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.erase(_container.begin());
	}

	T& front()
	{

		return _container.front();
	}

	bool empty()
	{
		return _container.empty();
	}

	int size()
	{
		return _container.size();
	}

private:
	list<T> _container;
};

int main()
{
	ArrayQueue<int> q;

	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}

	while (q.empty() == false)
	{
		int value = q.front();
		q.pop();
		cout << value << endl;
	}

	int size = q.size();
}