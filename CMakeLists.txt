cmake_minimum_required(VERSION 3.10.0)
project(Wordle VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

include_directories(src)

add_executable(Wordle src/main.cc src/dictionary.cc)
add_executable(Wordle_test test/dictionary_test.cc src/dictionary.cc)

target_link_libraries(Boost::program_options)

add_test(
  NAME WordleTest
  COMMAND Wordle_test.exe
)

include(CTest)
enable_testing()

