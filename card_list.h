// card_list.h
// Author: Misali Chigoji, Will Scott
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"
using namespace std;


class cardBST {

 public:
    // ctor, dtor, insert and one print method already done in cardBST.cpp:
    cardBST();                   // constructor
    ~cardBST();                  // destructor
    bool insert(string line);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // 8 METHODS YOU MUST IMPLEMENT in cardBST.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree

    // THESE ARE HARDER! DO THESE LAST
    int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
    int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(int value);                    // deletes the Node containing the given value from the tree

 private:

    struct Node {
	card* c;
	Node *left, *right, * parent;
	// useful constructor:
    Node(string v) : left(0), right(0), parent(0) {
        c = new card(v);
    }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(int value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(string value, int val, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value 
public:
    class iterator
    {
    private:
        Node* current;
    public:
        iterator(Node* ptr) : current(ptr) {}
        card* operator*() const;
        cardBST::iterator& cardBST::iterator::operator++();
        cardBST::iterator& cardBST::iterator::operator--();
    };

    iterator begin() const;
    iterator end() const;
    iterator rbegin() const;
    iterator rend() const;
};


#endif
