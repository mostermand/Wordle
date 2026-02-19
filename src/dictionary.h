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
#endif