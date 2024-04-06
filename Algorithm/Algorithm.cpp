#include <iostream>
#include <vector>
using namespace std;


template<typename T>
class Vector
{
public:
	Vector()
	{
		
	}

	~Vector()
	{
		if (_data)
		{
			delete _data;
		}
	}

	void pop_back()
	{
		delete _data[size--];
	}

	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
			{
				newCapacity++;
			}
			reserve(newCapacity);
		}
		_data[_size++] = value;
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity)
		{
			return;
		}

		T* temp = _data;
		_data = new T[capacity];
		for (int i = 0; i < _size; i++)
		{
			_data[i] = temp[i];
		}
		_capacity = capacity;
		delete temp;
	}

	T& operator[](const int pos)
	{
		return _data[pos];
	}

	int size()
	{
		return _size;
	}

	int capacity()
	{
		return _capacity;
	}

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}
		_size = 0;
	}

private:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;
};


int main()
{
	Vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << endl;
}
