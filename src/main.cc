#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//random numbers and time
#include <cstdlib>
#include <ctime>

#include "dictionary.h"




int main(int argc, char *argv[]) {
    std::ifstream wordle_ord("data/wordle_ord.txt");
    std::vector<std::string> dict;
    std::string solution;

    //Seed rng for today's random solution
    std::srand(std::time(0));
    //Initialize dictionary from wordlist file and pick a random solution
    readDict(wordle_ord, dict);
    solution = dict[rand()%dict.size()];
    
}
