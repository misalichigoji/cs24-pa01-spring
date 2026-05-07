// card.cpp
// Author: Misali Chigoji, Will Scott
// Implementation of the classes defined in card.h

class card {
    public:
        card(string line);
        string get_string();
    private:
        int value; //value between 1-52 ordered ascending, all clubs, then diamonds, then spades, then hearts
        string cardstring;
};

card::card(string line) : cardstring(line){
    //processing suit
    value = 0;
    if(line[0] == 'd')
        value += 13;
    else if(line[0] == 's')
        value += 26;
    else if(line[0] == 'h')
        value += 39;


    //
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
            value += (int)line[2];
    }
}

string card::get_string()
{
    return cardstring;
}
