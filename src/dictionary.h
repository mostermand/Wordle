#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

//Reads istream line by line into vector of strings
void readDict(std::istream& dictFile, std::vector<std::string>& dictOut);

//Checks if word is in dict
bool inDict(std::string word, const std::vector<std::string>& dict);

//Writes a vector of (bool,bool) for each letter in candidate: first bool is whether there is a positional match,
//second is if letter is in solution somewhere.
void matchWord(std::string candidate, std::string solution, std::vector<std::pair<bool, bool> >& matchOut);
#endif