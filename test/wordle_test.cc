#include <boost/test/unit_test.hpp>

#include <vector>
#include <string>

#include "wordle.h"

BOOST_AUTO_TEST_SUITE(wordle_test)

BOOST_AUTO_TEST_CASE(wordle_session) {
    std::string solution = "tying";
    std::vector<std::string> dictionary = {"scowl", "wager", "tying", "swarm", "shady"};
    WordleGame game(dictionary, solution);

    //word not in dictionary
    BOOST_TEST(game.guess("vegan") != 0);

    //word in dictionary but incorrect
    BOOST_TEST(game.guess("wager") == 0);

    //word in dictionary and correct
    BOOST_TEST(game.guess("tying") == 0);

    const WordleState& state = game.getState();

    //all the letters in the last(correct) guess are green
    bool allgreen = true;
    for(auto color : state.colorTable.back()) {
        allgreen = allgreen & color == LetterColor::Green;
    }
    BOOST_TEST(allgreen);

    //Does the game object agree that the game has been won?
    BOOST_TEST(game.hasWon());
}

BOOST_AUTO_TEST_CASE(double_letter) {
    std::string solution = "wager";
    std::vector<std::string> dictionary = {"naval", "wager", "spool", "ozone"};
    WordleGame game(dictionary, solution);
    const WordleState& state = game.getState();

    game.guess("naval");

    //first a in naval is green
    //LetterColor color = state.colorTable.back()[1];
    BOOST_TEST((state.colorTable.back()[1] == LetterColor::Green));
    BOOST_TEST((state.colorTable.back()[3] == LetterColor::Gray));

    game.init(dictionary, "spool");
    game.guess("ozone");

    BOOST_TEST((state.colorTable.back()[0] == LetterColor::Yellow));
    BOOST_TEST((state.colorTable.back()[2] == LetterColor::Green));
}

BOOST_AUTO_TEST_SUITE_END()