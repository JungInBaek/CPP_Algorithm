#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


struct Node
{
public:
	Node() {}
	Node(string data) { this->data = data; }

	string data;
	vector<Node*> children;
};

Node* CreateTree()
{
	Node* root = new Node("R1 개발실");
	{
		Node* node = new Node("디자인팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("전투");
			node->children.push_back(std::move(leaf));
		}
		{
			Node* leaf = new Node("경제");
			node->children.push_back(std::move(leaf));
		}
		{
			Node* leaf = new Node("스토리");
			node->children.push_back(std::move(leaf));
		}
	}
	{
		Node* node = new Node("프로그래밍팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("서버");
			node->children.push_back(std::move(leaf));
		}
		{
			Node* leaf = new Node("클라");
			node->children.push_back(std::move(leaf));
		}
		{
			Node* leaf = new Node("엔진");
			node->children.push_back(std::move(leaf));
		}
	}
	{
		Node* node = new Node("아트팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("배경");
			node->children.push_back(std::move(leaf));
		}
		{
			Node* leaf = new Node("캐릭터");
			node->children.push_back(std::move(leaf));
		}
	}

	return root;
}

void PrintTree(const Node& node, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}
	cout << " ";
	cout << node.data << endl;

	for(Node* child : node.children)
	{
		PrintTree(*child, depth + 1);
	}
}

int GetHeight(const Node& node)
{
	int height = 1;

	for (Node* child : node.children)
	{
		height = max(height, GetHeight(*child) + 1);
	}

	return height;
}

int main()
{
	Node& root = *CreateTree();

	PrintTree(root, 0);

	int height = GetHeight(root);

	cout << "height: " << height << endl;
}