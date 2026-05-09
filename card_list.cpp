// card_list.cpp
// Author: Misali Chigoji, Will Scott
// Implementation of the classes defined in card_list.h



#include "card_list.h"

#include <iostream>
using std::cout;

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
    delete n->c;
    delete n;
}

bool cardBST::insert(string line) {
    if(!root)
    {
        root = new Node(line);
        return true;
    }
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


// TODO: Change this to search by card instead of an int value.
cardBST::Node* cardBST::getNodeFor(int value , Node* n) const{
    if(!n)
        return NULL;
    if(n->c->get_value() == value)
        return n;
    if(n->c->get_value() > value)
        return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

// TODO: Change this to take a card instead of an int value.
bool cardBST::contains(int value) const {
    if(getNodeFor(value, root))
        return true;
    return false;
}

// TODO: This can be changed to work from a Node* or card instead of an int value.
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

// TODO: This can be changed to work from a Node* or card instead of an int value.
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

// TODO: Change this to take a card, and fix the two-child case so card ownership stays safe.
bool cardBST::remove(int value){
    Node* current = getNodeFor(value, root);
    if (!current) 
        return false;

    if (current->left && current->right) 
    {
        Node* pnode = getPredecessorNode(value);
        *(current->c) = *(pnode->c);
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

    delete current->c;
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
    if(!root)
        return iterator(nullptr);
    Node* temp = root;
    while(temp->left)
        temp = temp->left;
    return temp;
}
cardBST::iterator cardBST::end() const
{
    return iterator(nullptr);
}
cardBST::iterator cardBST::rbegin() const
{
    if(!root)
        return iterator(nullptr);
    Node* temp = root;
    while(temp->right)
        temp = temp->right;
    return temp;
}
cardBST::iterator cardBST::rend() const
{
    return iterator(nullptr);
}
bool cardBST::iterator::operator==(iterator i2)
{
    if(current == i2.current)
        return true;
    return false;
}
bool cardBST::iterator::operator!=(iterator i2)
{
    if(current != i2.current)
        return true;
    return false;
}
void playGame(cardBST alice, cardBST bob)
{
    bool copy = true;
  while(copy)
  {
    copy = false;

    for(auto aliceit = alice.begin(); aliceit != alice.end(); ++aliceit)
    {
      
      if(bob.contains((**aliceit).get_value()))
      {
        cout << "Alice picked matching card " << (*aliceit)->get_string() << endl;
         card temp = **aliceit;
         alice.remove(temp.get_value());  
         bob.remove(temp.get_value());
         copy = true;
         break;
      }
    }
    for(auto bobit = bob.rbegin(); bobit != bob.rend(); --bobit)
    {
      
      if(alice.contains((**bobit).get_value()))
      {
        cout << "Bob picked matching card " << (*bobit)->get_string() << endl;
         card temp = **bobit;
         bob.remove(temp.get_value());  
         alice.remove(temp.get_value());
         copy = true;
         break;
      }
    }
  }

  cout << endl << "Alice's cards:" << endl;
  for(auto it = alice.begin(); it != alice.end(); ++it)
    cout << (*it)->get_string() << endl;

  cout << endl << "Bob's cards:" << endl;
  for(auto it = bob.begin(); it != bob.end(); ++it)
    cout << (*it)->get_string() << endl;
}