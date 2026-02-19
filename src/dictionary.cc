#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "dictionary.h"

void readDict(std::istream& dictFile, std::vector<std::string>& dictOut) {
    std::string line;
    while(!dictFile.eof()) {
        std::getline(dictFile, line);
        if(line[0] != '#' && !line.empty()) {
            dictOut.push_back(line);
        }
        line.clear();
    }
}

bool inDict(std::string word, const std::vector<std::string>& dict) {
    return std::find(dict.begin(), dict.end(), word) != dict.end();
}