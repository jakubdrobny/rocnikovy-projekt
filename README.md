# Chromatic number of Scale-free graphs
Calculates chromatic number of Scale-free graphs generated using [Barabasi-Albert model](https://en.wikipedia.org/wiki/Barab%C3%A1si%E2%80%93Albert_model).

**WORKS ON LINUX ONLY.** *for now*

## Instructions
To run the program:
1. Download and install [CryptoMiniSAT](https://github.com/msoos/cryptominisat).
2. Clone this repository.
3. To run
    1. with g++, type the following into terminal (inside the cloned repository):
    ```g++ *.cpp -lcryptominisat5 -o main && ./main```
    2. with cmake:
        1. first create build directory (inside the cloned repository):
        ```mkdir build```
        2. build the project:
        ```mkdir build && cmake -S . -B ./build && cd build && make```
        3. now the executable code was created inside the build directory. to run it type into cmd (inside the build directory):
        ```./code```