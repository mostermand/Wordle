#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>

//random numbers and time
#include <cstdlib>
#include <ctime>

#include "dictionary.h"

template <std::size_t tableLength>
void printTable(const std::array<std::string, tableLength> table, const std::array<std::vector<std::pair<bool, bool> >, tableLength> table_comparisons) {
    for(auto row : table) {
        std::cout<<row<<"\n";
    }
}

void eventLoop(std::string solution, const std::vector<std::string>& dict) {
    const std::size_t tableLength = 6;
    std::array<std::string, tableLength> table = {};
    std::array<std::vector<std::pair<bool, bool> >, tableLength> table_comparisons = {};

    std::string line;
    std::size_t guessn = 0;
    while(true) {
        printTable(table, table_comparisons);
        std::cout<<">";
        std::getline(std::cin, line);
        if(inDict(line, dict)) {
            //make a guess
            table[guessn] = line;
            matchWord(line, solution, table_comparisons[guessn]);

            ++guessn;
            if(guessn < tableLength) {
                //not last guess
            } else {
                //last guess
                return;
            }
        } else {
            std::cout<<"Word is not in dictionary\n";
        }
    }
}

int main(int argc, char *argv[]) {
    std::ifstream wordle_ord("data/wordle_ord.txt");
    std::vector<std::string> dict;
    std::string solution;

    //Seed rng for today's random solution
    std::srand(std::time(0));
    //Initialize dictionary from wordlist file and pick a random solution
    readDict(wordle_ord, dict);
    solution = dict[rand()%dict.size()];

    eventLoop(solution, dict);
}
