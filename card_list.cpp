// card_list.cpp
// Author: Misali Chigoji, Will Scott
// Implementation of the classes defined in card_list.h



#include "card_list.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n)
        return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root)
    {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(n->info == value)
        return false;
    if(n->info > value)
    {
        if(!n->left)
        {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, n->left);
    }
    else
    {
        if(!n->right)
        {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, n->right);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    if(!root)
        return;
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n)
        return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n)
        return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n)
        return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n)
        return 0;
    return n->info + sum(n->left) +sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n)
        return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n)
        return NULL;
    if(n->info == value)
        return n;
    if(n->info > value)
        return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value, root))
        return true;
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* current = getNodeFor(value, root);
    if(!current)
        return NULL;
    if (current->left)
    {
        current = current->left;
        while(current->right)
            current = current->right;
        return current;
    }
    while (current->parent && current == current->parent->left)
        current = current->parent;
    return current->parent;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* pnode = getPredecessorNode(value);
    if(!pnode)
        return 0;
    return pnode->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* current = getNodeFor(value, root);
    if(!current)
        return NULL;
    if(current->right) //if there is a right subtree
    {
        current = current->right;
        while(current->left)
            current = current->left;
    }
    else if(current->parent)
    {
        while(current->parent && current != current->parent->left)
            current = current->parent;
        current = current->parent;
    }
    else
        current = NULL;
    return current;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* snode = getSuccessorNode(value);
    if(snode)
        return snode->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* current = getNodeFor(value, root);
    if (!current) 
        return false;

    if (current->left && current->right) 
    {
        Node* pnode = getPredecessorNode(value);
        current->info = pnode->info;
        current = pnode; 
    }

    Node* temp = NULL;
    if (current->left)
        temp = current->left;
    else
        temp = current->right;
    if (temp)
        temp->parent = current->parent;
    if (!current->parent)
        root = temp;
    else if (current == current->parent->left) 
        current->parent->left = temp;
    else 
        current->parent->right = temp;

    delete current;
    return true;
}