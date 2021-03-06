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

	// Root getter
	BSNode * getRoot() 
	{
		return this->root;
	}

	// Returns the value of the node with key needed
	V get(K key) 
	{
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

	// Adds the new node with predetermined key and value
	void add(K key, V value) 
	{
		BSNode	* current = root, 
				* parent = nullptr;
		
		while (current) 
		{
			if (current->key == key) 
			{
				current->value = value;
				return;
			}
			else
			{
				parent = current;
				if (current->key > key)
				{
					current = current->left;
				}
				else 
				{
					current = current->right;
				}
			}
		}
		BSNode * newNode = new BSNode(key, value);
		if (!parent)
		{
			root = newNode;
		}
		else
		{
			if (key < parent->key)
			{
				parent->left = newNode;
			}
			else
			{
				parent->right = newNode;
			}
		}
	}

	// Recursive realization
	BSNode * add(K key, V value, BSNode * node /* = root*/)		// A non static member can not be as a default paremeter in c++ 
	{														    // that's why I ain't gonna use recursive methods
		if (node == NULL)
		{
			node = new BSNode(key, value);
		}
		else if (key < node->key)
		{
			node->left = add(key, value, node->left);
		}
		else if (key > node->key)
		{
			node->right = add(key, value, node->right);
		}
	
		return node;
	}

	// Removes the node with predetermined key
	void remove(K key) 
	{
		BSNode	* current = root,
				* parent = nullptr;

		// Find the element needed
		while (current)
		{
			if (current->key == key)
			{
				break;
			}
			else
			{
				parent = current;
				if (current->key > key) {
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
		}

		// Check for invalid key
		if (!current)
		{
			return;
		}

		// It's easy if we the node hasn't a right subtree (first case) 
		if (!current->right)
		{
			if (!parent)
			{
				root = current->left;
			}
			else
			{
				if (current == parent->left) 
				{
					parent->left = current->left;
				}
				else 
				{
					parent->right = current->left;
				}
			}
		}

		// Find minimum in right subtree and replace it with the element needed
		else 
		{
			BSNode * leftMost = current->right;
			parent = nullptr;

			while (leftMost->left)
			{
				parent = leftMost;
				leftMost = leftMost->left;
			}
			if (parent)
			{
				parent->left = leftMost->right;
			}
			else
			{
				current->right = leftMost->right;
			}
			current->key = leftMost->key;
			current->value = leftMost->value;
		}
	}

	// Pre-order (we're checking roots before leaves)
	void preOrder(BSNode * node)
	{
		if (!node) 
		{
			return;
		}
		cout << "Key: " << node->key << " Value: " << node->value << endl;
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
		cout << "Key: " << node->key << " Value: " << node->value << endl;
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
		cout << "Key: " << node->key << " Value: " << node->value << endl;
	}

	private:
		// Root pointer
		BSNode * root;
};

int main()
{
	// Some simple tests
	BSTree<int, int> * tree = new BSTree<int, int>();

	tree->add(50, 1);
	tree->add(60, 1);
	tree->add(15, 1);
	tree->add(8, 1);
	tree->add(22, 1);
	tree->add(30, 1);
	tree->add(19, 1);
	tree->add(14, 1);
	tree->add(11, 1, tree->getRoot());

	cout << "\nPre-order :" << endl;
	tree->preOrder(tree->getRoot());

	cout << "\nIn-order :" << endl;
	tree->inOrder(tree->getRoot());

	cout << "\nPost-order :" << endl;
	tree->postOrder(tree->getRoot());

	system("pause");
    return 0;
}

