#pragma once


enum class Color
{
	RED = 0,
	BLACK = 1,
};

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
	Color color = Color::BLACK;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);

	void Insert(int key);
	void InsertFixUp(Node* node);

	void LeftRotate(Node* x);
	void RightRotate(Node* y);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};