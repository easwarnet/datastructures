//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	Node *root, *left, *right;
	Node (int data): root(nullptr), left(nullptr), right(nullptr)
	{
		this->data = data;
	}
};

class BST {
public:
	BST(int data) {
		Node *newNode = new Node(data);
		head = newNode;
	}

	BST(): head(nullptr) {

	}

	void addNode(Node *newNode) {
		if (newNode == nullptr) {
			return;
		}
		if(head == nullptr) {
			head = newNode;
		} else {
			addNodePriv(head, newNode);
		}
	}

	void findNode(int data) {
		findNodePriv(head, data);
	}

	void isBst() {
		if(isBstPriv(head)) {
			cout << "BST" << endl;
		} else {
			cout << "Not BST" << endl;
		}
	}

	void printLevelOrder() {
		int height = heightBstPriv(head);
		for (int i=1;i<=height;i++) {
			cout << "Level " << i << ": ";
			printLevelOrderGivenLevel(head, i);
			cout << endl;
		}
	}

	void heightBst() {
		cout << "Height of BST: " << heightBstPriv(head) << endl;
	}

	void buildBst() {
		vector<Node *> nodes;
		buildBstStoreValues(nodes, head);
		sort(nodes.begin(), nodes.end(), [](const Node *i, const Node *j) { return (i->data < j->data);});
		head = buildBstUtil(nodes, 0, nodes.size());
	}

	void findAndRemoveNode(int data) {
		Node *found = findNodePriv(head, data);
		if (removeNode(found)) {
			cout << "Deleted Node: " << data << endl;
		} else {
			cout << "Deleted Node Failed: " << data << endl;
		}
	}

	void inOrderTraversal() {
		if(head == nullptr) {
			cout << "Nothing to Print" << endl;
		} else {
			inOrderPrint(head);
		}
		cout << endl;
	}
	void preOrderTraversal() {
		if(head == nullptr) {
			cout << "Nothing to Print" << endl;
		} else {
			preOrderPrint(head);
		}
		cout << endl;
	}
	void postOrderTraversal() {
		if(head == nullptr) {
			cout << "Nothing to Print" << endl;
		} else {
			postOrderPrint(head);
		}
		cout << endl;
	}

private:
	void printLevelOrderGivenLevel(Node *cursor, int level) {
		if (cursor == nullptr) {
			return;
		}
		if(level == 1) {
			cout << cursor->data << " ";
		} else {
			printLevelOrderGivenLevel(cursor->left, level-1);
			printLevelOrderGivenLevel(cursor->right, level-1);
		}
	}

	void buildBstStoreValues(vector<Node *> &nodes, Node *cursor) {
		if(cursor == nullptr) {
			return;
		}

		buildBstStoreValues(nodes, cursor->left);
		nodes.push_back(cursor);
		buildBstStoreValues(nodes, cursor->right);
	}

	int heightBstPriv(Node *cursor) {
		if(cursor == nullptr) {
			return 0;
		}

		int lheight = heightBstPriv(cursor->left);
		int rheight = heightBstPriv(cursor->right);

		if(lheight > rheight) {
			return lheight + 1;
		} else {
			return rheight + 1;
		}
	}

	Node *buildBstUtil(vector<Node *> &nodes, int start, int end) {
		if((start > end) ) {
			return nullptr;
		}

		int mid = (start + end) / 2;
		Node *root = nodes[mid];

		if (root == nullptr)
			return nullptr;

		root->left = buildBstUtil(nodes, start, mid-1);
		root->right = buildBstUtil(nodes, mid+1, end);
		return root;
	}

	Node *addNodePriv(Node *cursor, Node *newNode) {
		if (cursor == nullptr) {
			cursor = newNode;
		} else {
			if(cursor->data < newNode->data) {
				cursor->right = addNodePriv(cursor->right, newNode);
				cursor->right->root = cursor;
			} else {
				cursor->left = addNodePriv(cursor->left, newNode);
				cursor->left->root = cursor;
			}
		}
		return cursor;
	}

	Node *findNodePriv(Node *cursor, int data) {
		if(cursor == nullptr) {
			return nullptr;
		}

		if(cursor->data == data) {
			if(cursor->root != nullptr)
				cout << "Root of Node of " << data << ": "<< cursor->root->data << endl;
			else {
				cout << "Root Node" << endl;
			}
			return cursor;
		}
		Node *foundNode = findNodePriv(cursor->left, data);
		return foundNode != nullptr ? foundNode : findNodePriv(cursor->right, data);
	}

	Node *findMinKey(Node *cursor) {
		while (cursor->left != nullptr)
		{
			cursor = cursor->left;
		}
		return cursor;

	}

	bool removeNode(Node *found) {
		bool retval = false;
		if ((found->left == nullptr) && (found->right == nullptr)) {
			if(found->root->left == found) {
				found->root->left = found->left;
			} else {
				found->root->right = found->right;
			}
			delete found;
			retval = true;
		} else if ((found->left != nullptr) && (found->right != nullptr)) {
			Node *cursor = findMinKey(found);
			found->data = cursor->data;
			if(cursor->root->left == cursor) {
				cursor->root->left = cursor->left;
			} else {
				cursor->root->right = cursor->right;
			}
			delete cursor;
			retval = true;
		} else {
			Node *cursor = (found->left == nullptr) ? found->right : found->left;
			found->data = cursor->data;
			delete cursor;
			retval = true;
		}

		return retval;
	}

	int isBstPriv(Node *cursor) {
		if(cursor == nullptr) {
			return 1;
		}

		if((cursor->left != nullptr) && (cursor->left->data > cursor->data)) {
			return 0;
		}
		
		if((cursor->right != nullptr) && (cursor->right->data < cursor->data)) {
			return 0;
		}

		if(!(isBstPriv(cursor->left)) || !(isBstPriv(cursor->right))) {
			return 0;
		}

		return 1;
	}

	void inOrderPrint(Node *cursor) {
		if(cursor == nullptr) {
			return;
		}
		inOrderPrint(cursor->left);
		cout << cursor->data << " " << cursor << " ";
		inOrderPrint(cursor->right);
	}
	void preOrderPrint(Node *cursor) {
		if(cursor == nullptr) {
			return;
		}
		cout << cursor->data << " ";
		preOrderPrint(cursor->left);
		preOrderPrint(cursor->right);
	}
	void postOrderPrint(Node *cursor) {
		if(cursor == nullptr) {
			return;
		}
		postOrderPrint(cursor->left);
		postOrderPrint(cursor->right);
		cout << cursor->data << " ";
	}

	Node *head;
};

int main() {
	/*
	*           8
	*         /   \
	*        /     \
	*       /       \
	*      6        10
	*    /   \    /    \
	*   5     7  9      11 
	*
	*   Inorder
	*   5 6 7
	*
	*   Preorder
	*   6 5 7
	*
	*   Postorder
	*   5 7 6
	*/

//	
	BST bst;
	bst.addNode(new Node(1));
	bst.addNode(new Node(2));
	bst.addNode(new Node(3));
	bst.addNode(new Node(4));
	bst.addNode(new Node(5));
	bst.addNode(new Node(6));
	bst.addNode(new Node(7));
	bst.addNode(new Node(8));
	bst.addNode(new Node(9));
	bst.addNode(new Node(10));
	bst.preOrderTraversal();
	bst.buildBst();
	bst.preOrderTraversal();
	bst.heightBst();
	bst.printLevelOrder();
//
	return 0;
}

void preinit() {
	BST bst(8);
	bst.addNode(new Node(6));
	bst.addNode(new Node(5));
	bst.addNode(new Node(7));
	bst.addNode(new Node(10));
	bst.addNode(new Node(9));
	bst.addNode(new Node(11));

	bst.isBst();
	bst.findNode(11);
	bst.inOrderTraversal();
	bst.findAndRemoveNode(11);

	bst.inOrderTraversal();
	bst.preOrderTraversal();
	bst.postOrderTraversal();
}

