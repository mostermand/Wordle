#ifndef WORDLE_H
#define WORDLE_H

#include <vector>
#include <string>
#include <array>

enum class LetterColor {
    Green,
    Yellow,
    Gray,
    White
};

//The public state of a wordle game
struct WordleState {
    std::vector<std::string> table;
    std::vector<std::vector<LetterColor>> colorTable;
    std::string alphabet;
    std::vector<LetterColor> alphabetColor;
};

class WordleGame {
public:
    WordleGame(std::vector<std::string> dictionary, std::string solution);
    void init(const std::vector<std::string> dictionary, std::string solution);
    int guess(std::string candidate);
    const WordleState& getState();
    bool hasWon();
    bool hasFinished();
private:
    std::string solution;
    std::vector<std::string> dictionary;
    WordleState state;
    bool won;
    bool finished;
};

#endif