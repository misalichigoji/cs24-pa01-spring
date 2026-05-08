// card.cpp
// Author: Misali Chigoji, Will Scott
// Implementation of the classes defined in card.h

#include "card.h"
using namespace std;

bool operator>(card c1, card c2)
{
    if(c1.get_value() > c2.get_value())
        return true;
    return false;
}
bool operator<(card c1, card c2)
{
    if(c1.get_value() < c2.get_value())
        return true;
    return false;
}
bool operator==(card c1, card c2)
{
    if(c1.get_value() == c2.get_value())
        return true;
    return false;
}
bool operator!=(card c1, card c2)
{
    if(c1.get_value() == c2.get_value())
        return false;
    return true;
}
ostream& operator<<(ostream& file, card c)
{
    file << c.get_string();
    return file;
}
card::card(string line) : cardstring(line){
    //processing suit
    value = 0;
    if(line[0] == 'd')
        value += 13;
    else if(line[0] == 's')
        value += 26;
    else if(line[0] == 'h')
        value += 39;


    //processing value
    if(line.length() > 3)
        value += 10;
    else
    {
        if(line[2] == 'a')
            value += 1;
        else if(line[2] == 'j')
            value += 11;
        else if(line[2] == 'q')
            value += 12;
        else if(line[2] == 'k')
            value += 13;
        else
            value += line[2] - '0';
    }
}

string card::get_string() const
{
    return cardstring;
}

int card::get_value() const
{
    return value;
}