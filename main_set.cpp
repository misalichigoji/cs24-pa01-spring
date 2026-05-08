// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  set<card> alice;
  set<card> bob;
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice.insert(card(line));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    bob.insert(card(line));
  }
  cardFile2.close();

  bool copy = true;

  while(copy)
  {
    auto aliceit = alice.begin();
    auto bobit = bob.begin();

    while(true)
    {
      if(*aliceit.get_value() == *bob.get_value)
      {
        cout << "Alice picked matching card " << *aliceit.get_string() << endl;
         card temp = *aliceit;
         aliceit++;
         alice.erase(temp);  
      }

    }
  }

  cout << "Alice's cards:" << endl;
  for(auto it = alice.begin(); it != alice.end(); ++it)
  {
    cout << *it.get_string() << endl;
  }

  cout << "Bob's cards:" << endl;
  for(auto it = bob.begin(); it != bob.end(); ++it)
  {
    cout << *it.get_string() << endl;
  }
  

  
  return 0;
}

