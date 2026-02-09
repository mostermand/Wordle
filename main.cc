#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dictionary.h"




int main(int argc, char *argv[]) {
    std::ifstream wordle_ord("data/wordle_ord.txt");
    std::vector<std::string> dict;

    std::cout<<"Hello, world!";

    readDict(wordle_ord, dict);
}
