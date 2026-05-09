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


    Node* getNodeFor(int value, Node* n) const; 
    void clear(Node *n); // for destructor
    bool insert(string value, int val, Node *n); 


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

    bool insert(string line);     // insert value; return false if duplicate


    bool contains(int value) const;  // true if value is in tree

    bool remove(int value);                    // deletes the Node containing the given value from the tree


    iterator begin() const;
    iterator end() const;
    iterator rbegin() const;
    iterator rend() const;
};

void playGame(cardBST alice, cardBST bob);
#endif
