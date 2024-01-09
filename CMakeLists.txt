cmake_minimum_required(VERSION 3.26)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp Graph.cpp History.cpp HistoryEntry.cpp Clause.cpp CNF.cpp Literal.cpp)
target_link_libraries(code PRIVATE cryptominisat5)