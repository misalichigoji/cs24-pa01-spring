// card.h
// Author: Misali Chigoji, Will Scott
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>
using namespace std;

class card {
    public:
        card(string line);
        string get_string();
        int get_value();
    private:
        int value; //value between 1-52 ordered ascending, all clubs, then diamonds, then spades, then hearts
        string cardstring; //string initially put into constructor, syntax program wants to see
};
bool operator>(card c1, card c2);
bool operator<(card c1, card c2);
bool operator==(card c1, card c2);
ostream& operator<<(ostream& file, card c);

#endif
