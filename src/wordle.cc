#include "wordle.h"
#include "dictionary.h"

WordleGame::WordleGame(std::vector<std::string> dictionary, std::string solution) {
    this->init(dictionary, solution);
}

void WordleGame::init(std::vector<std::string> dictionary, std::string solution) {
    this->state.alphabet = "qwertyuiopasdfghjklzxcvbnm";
    //initialize alphabetColor to all white
    this->state.alphabetColor.reserve(state.alphabet.size());
    this->state.alphabetColor.clear();
    for(int i = 0; i < state.alphabet.size(); ++i) { this->state.alphabetColor.emplace_back(LetterColor::White);}

    this->solution = solution;
    this->dictionary = dictionary;

    //Change solution to lower case
    for(auto& c : this->solution) {
        c = (char)std::tolower(c);
    }

    //Change dictionary to lower case
    for(auto& word : this->dictionary) {
        for(auto& c : word) {
            c = (char)std::tolower(c);
        }
    }

    this->won = false;
    this->finished = false;

    if(!inDict(this->solution, dictionary)) {
        //Error the proposed solution is not in the dictionary
    }
}

int WordleGame::guess(std::string candidate) {
    //if game has finished just return
    if(this->finished) {
        return 0;
    }
    if(!inDict(candidate, this->dictionary)) {
        //The word is not in the dictionary
        return -1;
    }

    //Add another word to table
    this->state.table.push_back(candidate);
    //Add another row to the color table; initialized to gray
    this->state.colorTable.emplace_back(std::initializer_list{LetterColor::Gray, LetterColor::Gray, LetterColor::Gray, LetterColor::Gray, LetterColor::Gray});

    //Mark letters in word as green
    for(int i = 0; i < 5; ++i) {
        if(solution[i] == candidate[i]) {
            this->state.colorTable.back()[i] = LetterColor::Green;
        }
    }
    //Mark letters in word as yellow
    for(int i = 0; i < 5; ++i) {
        //Letter is not green
        if(this->state.colorTable.back()[i] != LetterColor::Green) {
            //Find the index of the first occurence of the letter in solution that is not already a direct match
            std::size_t find_index = this->solution.find(this->state.table.back()[i], 0);
            //Indexing by find_index is safe since && shortcircuits
            while(find_index != std::string::npos && this->state.colorTable.back()[find_index] == LetterColor::Green) {
                find_index = this->solution.find(this->state.table.back()[i], find_index+1);
            }
            if(find_index != std::string::npos) {
                this->state.colorTable.back()[i] = LetterColor::Yellow;
            }
        }
    }

    //Color alphabet
    for(int wordI = 0; wordI < this->state.table.size(); ++wordI) {
        for(int cI = 0; cI < this->state.table[wordI].size(); ++cI) {
            std::size_t index_alphabet = this->state.alphabet.find(this->state.table[wordI][cI]);
            if(this->state.colorTable[wordI][cI] == LetterColor::Green) {
                this->state.alphabetColor[index_alphabet] = LetterColor::Green;
            } else if(this->state.colorTable[wordI][cI] == LetterColor::Yellow && this->state.alphabetColor[index_alphabet] != LetterColor::Green) {
                this->state.alphabetColor[index_alphabet] = LetterColor::Yellow;
            } else if(this->state.alphabetColor[index_alphabet] == LetterColor::White) {
                this->state.alphabetColor[index_alphabet] = LetterColor::Gray;
            }
        }
    }
    //test if guess was correct
    bool allgreen = true;
    for(auto color : this->state.colorTable.back()) {
        allgreen = allgreen && color == LetterColor::Green;
    }
    if(allgreen) {
        this->won = true;
        this->finished = true;
    }

    //Finished if sixth attempt
    if(this->state.table.size() >= 6) {
        this->finished = true;
    }
    return 0;
}

const WordleState& WordleGame::getState() {
    return this->state;
}

bool WordleGame::hasWon() {
    return this->won;
}
bool WordleGame::hasFinished() {
    return this->finished;
}