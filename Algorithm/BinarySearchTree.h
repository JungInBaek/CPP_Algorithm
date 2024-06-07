#pragma once


struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
};


class BinarySearchTree
{
public:
	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);

	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(Node* node);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);
	Node* Search(Node* node, int key);

	void Insert(int key);
	void Delete(int key);

private:
	Node* _root = nullptr;
};