// Including
#include "avl_tree.h"

// Node constructor
avl_tree::node::node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->leftCount = 0;
	this->rightCount = 0;
}

// Rotate tree
void avl_tree::rotate(direction dir)
{
	node* current;

	switch (dir)
	{
	case LEFT:
		current = head->right;
		head->right = head->right->left;
		current->left = head;
		head = current;
		break;
	case RIGHT:
		current = head->left;
		head->left = head->left->right;
		current->right = head;
		head = current;
		break;
	}
}

// Tree constructor
avl_tree::avl_tree()
{
	head = nullptr;
}

// Add new key to tree
void avl_tree::add(int key)
{
	if (head == nullptr)
	{
		head = new node(key);
	}
	else
	{
		node* current = head;

		while (true)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}

			if (current == nullptr)
			{
				current = new node(key);
				break;
			}
		}
	}
}

// Clear tree
void avl_tree::clear()
{

}

// Tree destructor
avl_tree::~avl_tree()
{
	clear();
}
