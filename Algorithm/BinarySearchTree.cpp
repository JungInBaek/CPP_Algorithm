#include "BinarySearchTree.h">
#include <Windows.h>
#include <iostream>

using namespace std;


void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
	{
		return;
	}

	SetCursorPosition(x, y);

	cout << node->key << endl;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
	cout << endl;
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
	cout << endl;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right)
	{
		return Min(node->right);
	}

	Node* parent = node->parent;
	while (parent && parent->right == node)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node->key == key)
	{
		return node;
	}

	while (node && node->key != key)
	{
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	return node;
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* parent = nullptr;
	Node* node = _root;
	while (node)
	{
		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	if (key < parent->key)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}

	newNode->parent = parent;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);

	if (deleteNode == nullptr)
	{
		return;
	}

	if (deleteNode->left == nullptr)
	{
		// deleteNode, deleteNode->right
		if (deleteNode->parent == nullptr)
		{
			_root = deleteNode->right;
		}
		else
		{
			deleteNode->parent->right = deleteNode->right;
		}

		if (deleteNode->right)
		{
			deleteNode->right->parent = deleteNode->parent;
		}

		delete deleteNode;
	}
	else if (deleteNode->right == nullptr)
	{
		// deleteNode, deleteNode->left
		if (deleteNode->parent == nullptr)
		{
			_root = deleteNode->left;
		}
		else
		{
			deleteNode->parent->left = deleteNode->left;
		}

		if (deleteNode->left)
		{
			deleteNode->left->parent = deleteNode->parent;
		}

		delete deleteNode;
	}
}
