//
//  main.cpp
//  assign6
//
//  Created by macbook on 7/15/19.
//  Copyright © 2019 team9. All rights reserved.
//
#include <iostream>
#include "tree.h"




void increase_size(node *root)
{
    while(root != NULL)
    {
	++root->size;
	root = root->parent;
    }
}


// Insert an item into the subtree rooted at "root".
// If x is already in the tree, it does nothing.
// Returns the new root.
// Should take time O(depth).
node* insert (node *root, int x)
{

    if (find(root, x)==NULL)
    {
    if (root == NULL)
    {
        root  = new node(x);
        return root;

    }
      else if (x == root->value) {
          return root;
          }

    else
    {
        
        
        if (x > root->value)
        {
           
            node* right_child = insert(root->right, x);
            root->right =right_child;
	    ++root->size;
            right_child->parent = root;

            
        }
        if (x < root->value)
        {
            
            node* left_child = insert(root->left, x);
            root->left = left_child;
	    ++root->size;
            left_child->parent = root;


            
        }
        return root;
    }
    }
    return root;
}

void decrease_size(node* root)
{
    while(root != NULL)
    {
	    --root->size;
	    root = root->parent;
    }
}

// Erases the node containing value "x" fromt the subtree rooted at "root".
// Returns the new root.
// Should take time O(depth).
node* erase (node *root, int x)
{
    if (find(root, x) != NULL)
    { 
	    if(root->value > x)
	    {
		    root->left = erase(root->left, x);
	    } else if(root->value < x)
	    {
		    root->right = erase(root->right, x);
	    } else {
		    if (root->left == NULL && root->right == NULL) {
			decrease_size(root);
			delete root;
			return nullptr;
		    }
		    else if (root->left == NULL || root->right == NULL) {
                decrease_size(root);
                node* parent = root->parent;
                node* temp = root;
                temp= root->left == NULL ? root->right : root->left;
                temp->parent = parent;
			delete root;
			return temp;
		    } else {
			node *temp = find_min(root->right);
			root->value = temp->value;
			root->right = erase(root->right,temp->value);

		    }
		    return root;
	    }
    }
    return root;
}

// Searches for a node with value "x" in the subtree rooted at "root",
// and returns a pointer to such node if found.
// Else it returns nullptr.
// Should take time O(depth).
node* find (node *root, int x) {
    if (root == NULL )
    {
        return nullptr;
    }
    else if (root->value == x) {
        return root;
    }
    else if (root->value > x)
        return find(root->left, x);
    else
        return find(root->right, x);
}

// Frees all nodes in the subtree rooted at "root".
// Should take time O(n).
void clear (node *root)
{
    if (root  == NULL) {
        return;
    }
    
    clear(root->right);
    clear(root->left);
    delete root;
}

// Makes a copy of the subtree rooted at "root", returns a pointer to the new root.
// Should take time O(n).
node* copy (node *root)
{
    if (root == NULL) {
        return root;
    }
    
    node *temp = new node(root->value);
    temp->left = copy(root->left);
    temp->size = root->size;
    temp->right = copy(root->right);
    temp->parent = root->parent;
    if (temp->left != nullptr)
    {
	    temp->left->parent = temp;
    }
    if (temp->right != nullptr)
    {
	    temp->right->parent = temp;
    }
    return temp;
}

// Finds the minimum of subtree rooted at "root".
// Should take time O(depth).
node* find_min (node *root) {
    node* min = root;
    if (root == NULL)
        return NULL;
    while (min->left) {
        min = min->left;
    }
    return min;
}

// Finds the maximum of subtree rooted at "root".
// Should take time O(depth).
node* find_max (node *root) {
    node* max = root;
    if (root == NULL)
        return NULL;
    while (max->right) {
        max = max->right;
    }
    return max;
}

// Finds the predecessor of the node "which".
// If "which" is nullptr, or the minimum node,
// should return nullptr.
// Should take time O(depth).
node* predecessor (node *which)
{
    node *predecessor = NULL;
    if (which  == NULL) {
        return nullptr;
    }
    if (which && which->left) {
        predecessor = find_max(which->left);
    }else {
        node* parent = which->parent;
        while (parent != nullptr) {
            if (parent->value < which->value)
                break;
            parent = parent->parent;
        }
        return parent;
    }
    return predecessor;
}

// Finds the predecessor of the node "which".
// If "which" is nullptr, or the maximum node,
// should return nullptr.
// Should take time O(depth).
node* successor (node *which) {
    node *successor = NULL;
    if (which  == NULL) {
        return nullptr;
    }
    if (which && which->right) {
        successor = find_min(which->right);
        return successor;
    } else {
        node* parent = which->parent;
        while (parent != NULL) {
            if (parent->value > which->value)
                break;
            parent = parent->parent;
        }
        return parent;
    }
    
}


// Finds the depth of the subtree rooted at "root".
// If the tree is empty, should return -1.
// Should take time O(n).
int depth (node *root)
{
    if (root == NULL)
        return -1;
    else {
           int depth1 = depth(root->right);
        int depth2 = depth(root->left);
        if (depth1 > depth2) {
            return (depth1 + 1); } else
                return (depth2 + 1);
    }
    
}

// Finds the kth smallest node in the subtree rooted at "root".
// If no such node exists, should return nullptr.
// Should take time O(depth).
node* find_by_rank (node *root, size_t k)
{
    if (root == nullptr)
        return root;
    
    if (root->left == nullptr)
    {
        if (k == 0) {
            return root;
        }
        return (find_by_rank(root->right, k - 1));

        
    }
    if (root->left->size > k)
    {
	return (find_by_rank(root->left, k));
    }

    if (root->left->size == k)
    {
        return root;
    }
    if (root->left->size < k && root->size > k)
    {
        return find_by_rank(root->right, k - root->left->size - 1);
    }
    return nullptr;
}



