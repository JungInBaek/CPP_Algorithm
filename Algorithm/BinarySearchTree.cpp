#include "BinarySearchTree.h">
#include <Windows.h>
#include <iostream>

using namespace std;


enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

//int maxY = 0;
void SetCursorPosition(int x, int y)
{
//	maxY = max(maxY, y);
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<WORD>(color));
}


BinarySearchTree::BinarySearchTree()
{
	_nil = new Node();
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
	{
		return;
	}
	
	SetCursorPosition(x, y);
	if (node->color == Color::RED)
	{
		SetCursorColor(ConsoleColor::RED);
	}
	else
	{
		SetCursorColor(ConsoleColor::BLUE);
	}

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
//	SetCursorPosition(0, maxY);
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left != _nil)
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right != _nil)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
	{
		return Min(node->right);
	}

	Node* parent = node->parent;
	while (parent != _nil && parent->right == node)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == _nil || node->key == key)
	{
		return node;
	}

	while (node->key != key)
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

	Node* parent = _nil;
	Node* node = _root;
	while (node != _nil)
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
	newNode->parent = parent;

	if (parent == _nil)
	{
		_root = newNode;
	}
	else if (key < parent->key)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}

	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::RED;

	InsertFixUp(newNode);
}

void BinarySearchTree::InsertFixUp(Node* node)
{
	while (node->parent->color == Color::RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::RED)
			{
				uncle->color = Color::BLACK;
				node->parent->color = Color::BLACK;
				node->parent->parent->color = Color::RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					LeftRotate(node);
				}

				node->parent->color = Color::BLACK;
				node->parent->parent->color = Color::RED;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::RED)
			{
				uncle->color = Color::BLACK;
				node->parent->color = Color::BLACK;
				node->parent->parent->color = Color::RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}

				node->parent->color = Color::BLACK;
				node->parent->parent->color = Color::RED;
				LeftRotate(node->parent->parent);
			}
		}
	}
	_root->color = Color::BLACK;
}

void BinarySearchTree::LeftRotate(Node* x)
{
	Node* y = x->right;

	x->right = y->left;
	if (y->left != _nil)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == _nil)
	{
		_root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void BinarySearchTree::RightRotate(Node* y)
{
	Node* x = y->left;

	y->left = x->right;
	if (x->right != _nil)
	{
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == _nil)
	{
		_root = x;
	}
	else if (y == y->parent->left)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}

	x->right = y;
	y->parent = x;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}
	else
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
	{
		_root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v)
	{
		v->parent = u->parent;
	}

	delete u;
}
