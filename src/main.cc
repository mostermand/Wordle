#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>

//random numbers and time
#include <cstdlib>
#include <ctime>

//console colors
#include <windows.h>

#include "dictionary.h"

//Used for console text color
static HANDLE hStdOut;
static WORD defaultColor;

template <std::size_t tableLength>
void printTable(const std::array<std::string, tableLength> table, const std::array<std::vector<std::pair<bool, bool> >, tableLength> table_comparisons) {
    const std::string alphabet = "qwertyuiopasdfghjklzxcvbnm";
    std::vector<std::array<bool, 3> > alphabetCmp(alphabet.size(), {false, false, false});

    for(std::size_t i = 0; i < tableLength; ++i) {
        for(std::size_t j = 0; j < table[i].size(); ++j) {
            //Find letters position in alphabet
            auto letterIndex = alphabet.find(table[i][j]);

            std::cout<<"[ ";
            if(table_comparisons[i][j].first) {
                //Letter is positional match
                SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
                //Mark letter as green
                alphabetCmp[letterIndex][0] = true;
            } else if(table_comparisons[i][j].second) {
                //Letter is general match
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
                //Mark letter as yellow
                alphabetCmp[letterIndex][1] = true;
            } else {
                //Letter is no match
                alphabetCmp[letterIndex][2] = true;
            }
            std::cout<<(char)std::toupper(table[i][j]);
            SetConsoleTextAttribute(hStdOut, defaultColor);
            std::cout<<" ]";
        }
        for(std::size_t j = 0; j < 5-table[i].size(); ++j) {
            //print the remaining table as empty
            std::cout<<"[   ]";
        }
        std::cout<<"\n";
    }
    //print alphabet
    std::cout<<"\n";
    for(std::size_t i = 0; i < alphabet.size(); ++i) {
        if(alphabetCmp[i][2]) {
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        } else if(alphabetCmp[i][0]) {
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        } else if(alphabetCmp[i][1]) {
            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
        }
        std::cout<<(char)std::toupper(alphabet[i]);
        SetConsoleTextAttribute(hStdOut, defaultColor);
    }
    std::cout<<"\n";
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
            if(line == solution) {
                printTable(table, table_comparisons);
                std::cout<<"Congratulations!\n";
                std::getline(std::cin, line);
                return;
            }
            if(guessn < tableLength) {
                //not last guess
            } else {
                std::cout<<"The correct answer was: "<<solution<<"\n";
                std::getline(std::cin, line);
                return;
            }
        } else {
            std::cout<<"Word is not in dictionary\n\n";
        }
    }
}

int main(int argc, char *argv[]) {
    std::ifstream wordle_ord("data/wordle_ord.txt");
    std::vector<std::string> dict;
    std::string solution;

    //initialize hStdOut; will not change 
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //Save default console color
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(hStdOut, &Info);
        defaultColor = Info.wAttributes;
    }
    //Seed rng for today's random solution
    std::srand(std::time(0));
    //Initialize dictionary from wordlist file and pick a random solution
    readDict(wordle_ord, dict);
    solution = dict[rand()%dict.size()];

    eventLoop(solution, dict);
}
