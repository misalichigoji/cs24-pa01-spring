// card_list.cpp
// Author: Misali Chigoji, Will Scott
// Implementation of the classes defined in card_list.h



#include "card_list.h"

#include <iostream>
using std::cout;
template<typename cardBST>
class CardIterator
{
public:
    CardIterator();
    CardIterator begin();
};
CardIterator begin()
{
    return CardIterator();
}
// constructor sets up empty tree
cardBST::cardBST() { 
    root = nullptr;
}

// destructor deletes all nodes
cardBST::~cardBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void cardBST::clear(Node *n) {
    if(!n)
        return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool cardBST::insert(string line) {
    if(!root)
    {
        root = new Node(line);
        return true;
    }
    int num(0);
    int val = 0;
    if(line[0] == 'd')
        val += 13;
    else if(line[0] == 's')
        val += 26;
    else if(line[0] == 'h')
        val += 39;


    //processing value
    if(line.length() > 3)
        val += 10;
    else
    {
        if(line[2] == 'a')
            val += 1;
        else if(line[2] == 'j')
            val += 11;
        else if(line[2] == 'q')
            val += 12;
        else if(line[2] == 'k')
            val += 13;
        else
            val += line[2] - '0';
    }
    return insert(line, val, root);
}

// recursive helper for insert (assumes n is never 0)
bool cardBST::insert(string value, int val, Node *n) {
    if(n->c->get_string() == value)
        return false;
    if(n->c->get_value() > val)
    {
        if(!n->left)
        {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, val, n->left);
    }
    else
    {
        if(!n->right)
        {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, val, n->right);
    }
}

// print tree data pre-order
void cardBST::printPreOrder() const {
    if(!root)
        return;
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void cardBST::printPreOrder(Node *n) const {
    if(!n)
        return;
    cout << n->c->get_string() << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void cardBST::printInOrder() const {
    printInOrder(root);
}
void cardBST::printInOrder(Node *n) const {
    if(!n)
        return;
    printInOrder(n->left);
    cout << n->c->get_string() << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void cardBST::printPostOrder() const {
    printPostOrder(root);
}

void cardBST::printPostOrder(Node *n) const {
    if(!n)
        return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->c->get_string() << " ";
}


// return count of values
int cardBST::count() const {
    return count(root);
}

// recursive helper for count
int cardBST::count(Node *n) const {
    if(!n)
        return 0;
    return 1 + count(n->left) + count(n->right);
}


cardBST::Node* cardBST::getNodeFor(int value, Node* n) const{
    if(!n)
        return NULL;
    if(n->c->get_value() == value)
        return n;
    if(n->c->get_value() > value)
        return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool cardBST::contains(int value) const {
    if(getNodeFor(value, root))
        return true;
    return false;
}

// returns the Node containing the predecessor of the given value
cardBST::Node* cardBST::getPredecessorNode(int value) const{
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
int cardBST::getPredecessor(int value) const{
    Node* pnode = getPredecessorNode(value);
    if(!pnode)
        return 0;
    return pnode->c->get_value();
}

// returns the Node containing the successor of the given value
cardBST::Node* cardBST::getSuccessorNode(int value) const{
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
int cardBST::getSuccessor(int value) const{
    Node* snode = getSuccessorNode(value);
    if(snode)
        return snode->c->get_value();
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool cardBST::remove(int value){
    Node* current = getNodeFor(value, root);
    if (!current) 
        return false;

    if (current->left && current->right) 
    {
        Node* pnode = getPredecessorNode(value);
        current->c = pnode->c;
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

card* cardBST::iterator::operator*() const 
    {
        return current->c;
    }
cardBST::iterator& cardBST::iterator::operator++()
{
    if (current == nullptr)
        return *this;
        
    if (current->right)
    {
        current = current->right;

        while (current->left)
            current = current->left;
    }
    else
    {
        Node* parent = current->parent;

        while (parent && current == parent->right)
        {
            current = parent;
            parent = parent->parent;
        }

        current = parent;
    }

    return *this;
}
cardBST::iterator& cardBST::iterator::operator--()
{
    if(current == nullptr)
        return *this;
    
    if(current->left)
    {
        current = current->left;
        while(current->right)
            current = current-> right;
    }
    else
    {
        Node* parent = current->parent;

        while (parent && current == parent->left)
        {
            current = parent;
            parent = parent->parent;
        }

        current = parent;
    }

    return *this;
}
cardBST::iterator cardBST::begin() const
{

}