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

	void Print();
	void Print(Node* node, int x, int y);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);
	Node* Search(Node* node, int key);

	void Insert(int key);

	void InsertFixup(Node* node);
	void LeftRotate(Node* x);
	void RightRotate(Node* y);

	void Delete(int key);
	void Delete(Node* node);
	void DeleteFixup(Node* node);

	void Replace(Node* u, Node* v);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};