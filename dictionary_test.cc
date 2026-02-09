#define BOOST_TEST_MODULE dictionary_test
#include <boost/test/included/unit_test.hpp>

#include "dictionary.h"

BOOST_AUTO_TEST_CASE(first_test)
{
  std::ifstream wordle_ord("data/wordle_ord.txt");
  std::vector<std::string> dict;

  readDict(wordle_ord, dict);
}