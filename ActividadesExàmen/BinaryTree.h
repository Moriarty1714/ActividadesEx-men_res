#pragma once
#include <stack>

template <typename T>
class BinaryTree {
	struct Node
	{
		T data;

		Node* left;
		Node* right;

		Node(T _data) : data(_data), left(nullptr), right(nullptr) {};
	};

public:
	Node *root;

	BinaryTree() {
		root = new Node(23);
		root->left = new Node(65);
		root->right = new Node(95);
		root->left->right = new Node(34);
		root->left->left = new Node(25);
		root->right->left = new Node(36);
		root->right->left->left = new Node(86);
	}

	~BinaryTree() {
		DestroyTree(root);
	}

	void DestroyTree(Node* _node) {
		if (_node->left == nullptr && _node->right == nullptr) delete _node;
		else {
			if (_node->left != nullptr) DestroyTree(_node->left);
			if (_node->right != nullptr) DestroyTree(_node->right);
		}
	}

	void PreOrder(Node* _node) {
		if (_node == nullptr) return;
		std::cout << _node->data <<" " <<std::flush;
		PreOrder(_node->left);
		PreOrder(_node->right);
	}

	void InOrder(Node* _node) {
		if (_node == nullptr) return;
		PreOrder(_node->left);
		std::cout << _node->data << " " << std::flush;
		PreOrder(_node->right);
	}

	void PostOrder(Node* _node) {
		if (_node == nullptr) return;
		PreOrder(_node->left);
		PreOrder(_node->right);
		std::cout << _node->data << " " << std::flush;
	}
	
	int GetNumberNodes(Node* _node) {
		if (_node == nullptr) return 0;
		return 1 + GetNumberNodes(_node->left) + GetNumberNodes(_node->right);
	}

	int  GetNumberNodesI() {
		if (root == nullptr)return 0;
		int count = 0;

		std::stack<Node*> notVisitedNodes;
		notVisitedNodes.push(root);
		Node* tmp;

		while (!notVisitedNodes.empty()) {
			tmp = notVisitedNodes.top();
			notVisitedNodes.pop();
			counter++;

			if (tmp->left != nullptr) notVisitedNodes.push(tmp->left);
			if (tmp->right != nullptr) notVisitedNodes.push(tmp->right);

			delete tmp;
		}
		return counter;
	}
};