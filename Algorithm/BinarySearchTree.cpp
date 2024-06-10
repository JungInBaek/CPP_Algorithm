#pragma once
#include "BinarySearchTree.h"
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

short maxY = 0;
void SetCursorPosition(int x, int y)
{
	maxY = max(maxY, y);
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<WORD>(color));
}

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
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

void BinarySearchTree::Print()
{
	::system("cls");
	ShowConsoleCursor(false);
	Print(_root, 10, 0);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
	{
		--maxY;
		return;
	}

	SetCursorPosition(x, y);
	if (node->color == Color::BLACK)
	{
		SetCursorColor(ConsoleColor::BLUE);
	}
	else
	{
		SetCursorColor(ConsoleColor::RED);
	}

	cout << node->key;

	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
	SetCursorPosition(0, maxY + 1);
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
	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	while (node != _nil && node->key != key)
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

	newNode->color = Color::RED;
	newNode->left = _nil;
	newNode->right = _nil;

	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
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

	x->parent = y;
	y->left = x;
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

	y->parent = x;
	x->right = y;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
	{
		return;
	}

	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, node->right);

		if (color == Color::BLACK)
		{
			DeleteFixup(right);
		}
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, node->left);

		if (color == Color::BLACK)
		{
			DeleteFixup(left);
		}
	}
	else
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::DeleteFixup(Node* node)
{
	Node* x = node;
	while (x->parent != _nil && x->color == Color::BLACK)
	{
		if (x == x->parent->left)
		{
			Node* sibling = x->parent->right;
			if (sibling->color == Color::RED)
			{
				sibling->color = Color::BLACK;
				x->parent->color = Color::RED;
				LeftRotate(x->parent);
				sibling = x->parent->right;
			}
			else
			{
				if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK)
				{
					sibling->color = Color::RED;
					x = x->parent;
				}
				else
				{
					if (sibling->right->color == Color::BLACK)
					{
						sibling->color = Color::RED;
						sibling->left->color = Color::BLACK;
						RightRotate(sibling);
						sibling = x->parent->right;
					}

					sibling->color = x->parent->color;
					x->parent->color = Color::BLACK;
					sibling->right->color = Color::BLACK;
					LeftRotate(x->parent);
					x = _root;
				}
			}
		}
		else
		{
			Node* sibling = x->parent->left;
			if (sibling->color == Color::RED)
			{
				sibling->color = Color::BLACK;
				x->parent->color = Color::RED;
				RightRotate(x->parent);
				sibling = x->parent->left;
			}
			else
			{
				if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK)
				{
					sibling->color = Color::RED;
					x = x->parent;
				}
				else
				{
					if (sibling->left->color == Color::BLACK)
					{
						sibling->color = Color::RED;
						sibling->right->color = Color::BLACK;
						LeftRotate(sibling);
						sibling = x->parent->left;
					}

					sibling->color = x->parent->color;
					x->parent->color = Color::BLACK;
					sibling->left->color = Color::BLACK;
					RightRotate(x->parent);
					x = _root;
				}
			}
		}
	}
	x->color = Color::BLACK;
}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
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

	v->parent = u->parent;

	delete u;
}
