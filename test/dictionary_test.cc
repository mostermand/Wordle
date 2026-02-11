#define BOOST_TEST_MODULE dictionary_test
#include <boost/test/included/unit_test.hpp>

#include "dictionary.h"

BOOST_AUTO_TEST_CASE(compare_dictionary_file) {
  std::ifstream wordle_ord("data/wordle_ord.txt");
  std::vector<std::string> dict;

  //read dictionary normally
  readDict(wordle_ord, dict);
  wordle_ord.close();

  //reopen file and verify we get same result by reading line by line
  std::ifstream wordle_ord_dup("data/wordle_ord.txt");
  std::string cmpstring;
  int counter = 0;
  while(!wordle_ord_dup.eof()) {
    std::getline(wordle_ord_dup, cmpstring);
    if(cmpstring[0] != '#' && !cmpstring.empty()) {
      BOOST_TEST(dict.at(counter) == cmpstring);
      ++counter;
    }
  }
}

BOOST_AUTO_TEST_CASE(find_word_in_dict) {
  std::ifstream wordle_ord("data/wordle_ord.txt");
  std::vector<std::string> dict;

  //read dictionary
  readDict(wordle_ord, dict);
  wordle_ord.close();

  BOOST_TEST(inDict(std::string("crimp"), dict));
  BOOST_TEST(inDict(std::string("shard"), dict));
  BOOST_TEST(inDict(std::string("spool"), dict));

  BOOST_TEST(!inDict(std::string("qwert"), dict));
}

BOOST_AUTO_TEST_CASE(match_word_cases) {
  std::string solution = "vegan";
  std::string candidate = "death";
  std::ifstream wordle_ord("data/wordle_ord.txt");
  std::vector<std::string> dict;

  //read dictionary
  readDict(wordle_ord, dict);
  wordle_ord.close();

  BOOST_TEST(inDict(solution, dict));
  BOOST_TEST(inDict(candidate, dict));

  std::vector<std::pair<bool, bool> > comparison;
  matchWord(candidate, solution, comparison);

  //not matching letter
  BOOST_TEST(comparison[0].first == false);
  BOOST_TEST(comparison[0].second == false);

  //general match
  BOOST_TEST(comparison[2].first == false);
  BOOST_TEST(comparison[2].second == true);

  //positional match
  BOOST_TEST(comparison[1].first == true);
  BOOST_TEST(comparison[1].second == true);
}

BOOST_AUTO_TEST_CASE(pos_match_imply_gen_match) {
  std::ifstream wordle_ord("data/wordle_ord.txt");
  std::vector<std::string> dict;

  //read dictionary
  readDict(wordle_ord, dict);
  wordle_ord.close();

  std::string solution = "vegan";
  for(auto candidate: dict) {
    std::vector<std::pair<bool, bool> > comparison;

    BOOST_TEST(inDict(solution, dict));
    BOOST_TEST(inDict(candidate, dict));

    matchWord(candidate, solution, comparison);
    for(auto match : comparison) {
      BOOST_TEST((!match.first || match.second)); // position match implies general match
    }

    comparison.clear();
  }
}