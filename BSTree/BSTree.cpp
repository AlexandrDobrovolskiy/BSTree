// BSTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename K, typename V> class BSTree 
{
public:
	class BSNode 
	{
	public:
		K key;
		V value;
		BSNode	* left, 
				* right;

		BSNode(K key, V value) 
		{
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	//root pointer
	BSNode * root;

	//returns the value of the node with key needed
	V get(K key) {
		BSNode * temp = root;

		while (temp) 
		{
			if (key == temp->key) 
			{
				return temp->value;
			}
			else if(key < temp->key) 
			{
				temp = temp->left;
			}
			else 
			{
				temp = temp->right;
			}
		}

		return NULL;
	}

	//adds the new node with predetermined key and value
	void add(K key, V value) 
	{
		BSNode	* x = root, 
				* y = nullptr;
		
		while (x) 
		{
			if (x->key == key) 
			{
				x->value = value;
				return;
			}
			else
			{
				y = x;
				if (x->key > key)
				{
					x = x->left;
				}
				else 
				{
					x = x->right;
				}
			}
		}
		BSNode * newNode = new BSNode(key, value);
		if (!y)
		{
			root = newNode;
		}
		else
		{
			if (key < y->key)
			{
				y->left = newNode;
			}
			else
			{
				y->right = newNode;
			}
		}
	}

	//removes the node with predetermined key
	void remove(K key) 
	{
		BSNode	* x = root,
				* y = nullptr;

		// Find the element needed
		while (x)
		{
			if (x->key == key)
			{
				break;
			}
			else
			{
				y = x;
				if (x->key > key) {
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}
		}
		// Check for invalid key
		if (!x)
		{
			return;
		}
		// It's easy if we the node hasn't a right subtree (first case) 
		if (!x->right)
		{
			if (!y)
			{
				root = x->left;
			}
			else
			{
				if (x == y->left) 
				{
					y->left = x->left;
				}
				else 
				{
					y->right = x->left;
				}
			}
		}
		// Find minimum in right subtree and replace it with the element needed
		else 
		{
			BSNode * leftMost = x->right;
			y = nullptr;

			while (leftMost->left)
			{
				y = leftMost;
				leftMost = leftMost->left;
			}
			if (y)
			{
				y->left = leftMost->right;
			}
			else
			{
				x->right = leftMost->right;
			}
			x->key = leftMost->key;
			x->value = leftMost->value;
		}
	}

	//Pre-order (we're checking roots before leaves)
	void preOrder(BSNode * node)
	{
		if (!node) 
		{
			return;
		}
		cout << "Key: " << node->key << " Data: " << node->value << endl;
		preOrder(node->left);
		preOrder(node->right);
	}

	// In-order (we're checking childs before parents)
	void inOrder(BSNode * node) 
	{
		if (!node)
		{
			return;
		}
		inOrder(node->left);
		cout << "Key: " << node->key << " Data: " << node->value << endl;
		inOrder(node->right);
	}

	// Post-order (begins from leaves and ends by root)
	void postOrder(BSNode * node) 
	{
		if (!node)
		{
			return;
		}
		postOrder(node->left);
		postOrder(node->right);
		cout << "Key: " << node->key << " Data: " << node->value << endl;
	}
};

int main()
{
	// Some simple tests
	BSTree<int, int> * tree = new BSTree<int, int>();

	tree->add(0, 6);
	tree->add(1, 12);
	tree->add(2, 23);
	tree->add(3, 54);
	tree->add(4, 19);
	tree->add(5, 64);
	tree->add(6, 21);
	tree->add(7, 75);


	cout << "\nPre-order :" << endl;
	tree->preOrder(tree->root);

	cout << "\nIn-order :" << endl;
	tree->inOrder(tree->root);

	cout << "\nPost-order :" << endl;
	tree->postOrder(tree->root);

	system("pause");
    return 0;
}

