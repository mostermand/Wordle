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

void matchWord(std::string candidate, std::string solution, std::vector<std::pair<bool, bool> >& matchOut) {
    bool posMatch, genMatch; // posMatch: letter matched exact position; genMatch: letter is in word.
    for(int i = 0; i < candidate.size() && i < solution.size(); ++i) {
        posMatch = candidate[i] == solution[i];
        genMatch = solution.find(candidate[i]) != std::string::npos;
        matchOut.push_back(std::make_pair(posMatch, genMatch));
    }
}