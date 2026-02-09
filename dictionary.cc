#include <iostream>
#include <string>
#include <vector>

#include "dictionary.h"

void readDict(std::istream& dictFile, std::vector<std::string>& dictOut) {
    std::string line;
    while(!dictFile.eof()) {
        std::getline(dictFile, line);
        if(line[0] != '#') {
            dictOut.push_back(line);
        }
        line.clear();
    }
}