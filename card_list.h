// card_list.h
// Author: Misali Chigoji, Will Scott
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"
using namespace std;


class cardBST {
private:
    struct Node {
	card* c;
	Node *left, *right, * parent;
	    Node(string v) : left(0), right(0), parent(0) {
	        c = new card(v);
	    }
	};

	Node *root;

    // TODO: Change this to search by card instead of an int value.
    Node* getNodeFor(int value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    // TODO: Eventually pass a card through insertion instead of a separate string and int.
    bool insert(string value, int val, Node *n); // note overloading names for simplicity
    void printInOrder(Node *n) const;

    // TODO: These can be changed to work from a Node* or card instead of an int value.
    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value 


public:
    class iterator {
    private:
        Node* current;
    public:
        iterator(Node* ptr) : current(ptr) {}
        card* operator*() const;
        iterator& operator++();
        iterator& operator--();
        bool operator==(iterator i2);
        bool operator!=(iterator i2);
    };

    cardBST();                   // constructor
    ~cardBST();                  // destructor

    // TODO: Eventually insert should build a card once and compare using card operators.
    bool insert(string line);     // insert value; return false if duplicate

    // TODO: Print each card on its own line for the final hand output.
    void printInOrder() const;       // print tree data in-order to cout

    // TODO: Change this to take a card instead of an int value.
    bool contains(int value) const;  // true if value is in tree

    // TODO: Change this to take a card instead of an int value.
    bool remove(int value);                    // deletes the Node containing the given value from the tree


    iterator begin() const;
    iterator end() const;
    iterator rbegin() const;
    iterator rend() const;
};


#endif
