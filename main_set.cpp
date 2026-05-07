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
  vector<string> hand1;
  vector<string> hand2;
  while (getline (cardFile1, line) && (line.length() > 0)){
    hand1.push_back(line);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    hand2.push_back(line);
  }
  cardFile2.close();
  
  
  return 0;
}

