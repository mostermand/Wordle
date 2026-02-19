//#define BOOST_TEST_MODULE dictionary_test
#include <boost/test/unit_test.hpp>

#include <fstream>

#include "dictionary.h"

BOOST_AUTO_TEST_SUITE(dictionary_test)

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

BOOST_AUTO_TEST_SUITE_END()