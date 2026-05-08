// card.h
// Author: Misali Chigoji, Will Scott
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>

class card {
    public:
        card(std::string line);
        std::string get_string() const;
        int get_value() const;
    private:
        int value; //value between 1-52 ordered ascending, all clubs, then diamonds, then spades, then hearts
        std::string cardstring; //string initially put into constructor, syntax program wants to see
};
bool operator>(card c1, card c2);
bool operator<(card c1, card c2);
bool operator==(card c1, card c2);
bool operator!=(card c1, card c2)
std::ostream& operator<<(std::ostream& file, card c);

#endif
