// Protection for repeat including
#pragma once

// Enum type for direction
enum direction
{
	LEFT, RIGHT
};

// AVL-TRee
class avl_tree
{
private:
	// Tree node
	class node
	{
	public:
		node* left, * right;
		int key;

		int leftCount, rightCount;

		node(int key);
	};

	node* head; // Head of tree

	void rotate(direction dir);
public:
	avl_tree();
	void add(int key);
	void clear();
	~avl_tree();
};

