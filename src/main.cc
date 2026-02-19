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
#include "wordle.h"

//Used for console text color
static HANDLE hStdOut;
static WORD defaultColor;

void printTable(const WordleState& state) {
    for(std::size_t i = 0; i < 6; ++i) {
        for(std::size_t j = 0; j < 5; ++j) {
            std::cout<<"[ ";
            if(i < state.table.size()) {
                switch(state.colorTable[i][j])
                {
                case LetterColor::Green:
                    //Console color green
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
                    break;
                case LetterColor::Yellow:
                    //Console color yellow
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
                    break;
                default:
                    //Console color blue
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
                }
                std::cout<<(char)std::toupper(state.table[i][j]);
                SetConsoleTextAttribute(hStdOut, defaultColor);
            } else {
                std::cout<<" ";
            }
            std::cout<<" ]";
        }
        std::cout<<"\n";
    }
    //print alphabet
    std::cout<<"\n";
    for(std::size_t i = 0; i < state.alphabet.size(); ++i) {
        switch(state.alphabetColor[i])
        {
        case LetterColor::Green:
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            break;
        case LetterColor::Yellow:
            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case LetterColor::Gray:
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            break;
        case LetterColor::White:
            SetConsoleTextAttribute(hStdOut, defaultColor);
            break;
        }
        std::cout<<(char)std::toupper(state.alphabet[i]);
    }
    SetConsoleTextAttribute(hStdOut, defaultColor);
    std::cout<<"\n";
}

void eventLoop(WordleGame& game, std::string solution) {
    std::string line;
    const WordleState& state = game.getState();

    printTable(state);
    while(true) {
        std::cout<<">";
        std::getline(std::cin, line);

        if(game.guess(line)) {
            std::cout<<"Word is not in dictionary\n\n";
        }
        printTable(state);
        if(game.hasFinished()) {
            if(game.hasWon()) {
                std::cout<<"Congratulations!\n";
                std::getline(std::cin, line);
                return;
            } else {
                std::cout<<"The correct answer was: "<<solution<<"\n";
                std::getline(std::cin, line);
                return;
            }
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

    WordleGame game(dict, solution);

    eventLoop(game, solution);
}
