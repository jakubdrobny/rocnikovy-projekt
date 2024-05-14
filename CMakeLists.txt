cmake_minimum_required(VERSION 3.26)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp Graph.cpp History.cpp HistoryEntry.cpp solver/Clause.cpp solver/lit.cpp solver/Vector.cpp solver/lbool.cpp solver/Queue.cpp solver/Solver.cpp solver/Constr.cpp CNF.cpp Literal.cpp)
target_link_libraries(code PRIVATE cryptominisat5)