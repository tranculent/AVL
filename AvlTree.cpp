#pragma once
#ifndef AVL_TREE
#define AVL_TREE

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>

using namespace std;

struct AVL {
	int val;
	struct AVL* left;
	struct AVL* right;
} *right; // define an object of type *AVL called right

class AvlTree {
public:
	int height(AVL*);
	int height_difference(AVL*);
	AVL* rr_rotate(AVL*);
	AVL* ll_rotate(AVL*);
	AVL* lr_rotate(AVL*);
	AVL* rl_rotate(AVL*);
	AVL* balance(AVL*);
	AVL* insert(AVL*, int);
	void preorder(AVL*);
};

int AvlTree::height(AVL* tree) {
	int h = 0;

	if (tree != NULL) {
		int leftHeight = height(tree->left);
		int rightHeight = height(tree->right);
		int maxHeight = std::max(leftHeight, rightHeight);
		h = maxHeight + 1;
	}

	return h;
}

int AvlTree::height_difference(AVL* tree) {
	int leftHeight = height(tree->left);
	int rightHeight = height(tree->right);
	return leftHeight - rightHeight;
}

AVL* AvlTree::rr_rotate(AVL* parent) {
	AVL* temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

AVL* AvlTree::ll_rotate(AVL* parent) {
	AVL* temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

AVL* AvlTree::rl_rotate(AVL* parent) {
	AVL* temp = parent->left;
	parent->left = rr_rotate(temp);
	return ll_rotate(parent);
}

AVL* AvlTree::lr_rotate(AVL* parent) {
	AVL* temp = parent->right;
	parent->right = ll_rotate(temp);
	return rr_rotate(parent);
}

// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ use as a reference
AVL* AvlTree::balance(AVL* tree) {
	int balanceFactor = height_difference(tree);
	if (balanceFactor > 1) {
		if (height_difference(tree->left) > 0) {
			tree = ll_rotate(tree);
		}
		else {
			// if the right height is greater than the left
			tree = lr_rotate(tree);
		}
	}
	// if the right height is greater than the left
	else if (balanceFactor < -1) {
		// if the left height is greater than the right
		if (height_difference(tree->right) > 0) {
			tree = rl_rotate(tree);
		}
		else {
			tree = rr_rotate(tree);
		}
	}

	return tree;
}

/*

		30                                           35
	  /    \                                        /  \
	5		35      ---insert(root,45)--->         30   40  
		  /    \                                  /  \    \
		32		40                               5   32   45

*/
AVL* AvlTree::insert(AVL* root, int value) {
	// base case
	if (root == NULL) {
		root = new AVL;
		root->val = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->val) {
		root->left = insert(root->left, value);
		root = balance(root); // balance new sub-tree
	}
	else if (value >= root->val) {
		root->right = insert(root->right, value);
		root = balance(root); // balance new sub-tree
	}
	else {
		return root; // equal root values are not allowed
	}

	return root;
}

// Print tree
void AvlTree::preorder(AVL* t) {
	if (t == NULL)
		return;
	cout << t->val << " ";
	preorder(t->left);
	preorder(t->right);
}

#endif
