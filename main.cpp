// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

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
  cardBST alice;
  cardBST bob;
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice.insert(line);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    bob.insert(line);
  }
  cardFile2.close();

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
    for(auto bobit = bob.rbegin(); bobit != bob.rend(); ++bobit)
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
  {
    cout << (*it)->get_string() << endl;
  }

  cout << endl << "Bob's cards:" << endl;
  for(auto it = bob.begin(); it != bob.end(); ++it)
  {
    cout << (*it)->get_string() << endl;
  }
  

  
  return 0;
}

  

