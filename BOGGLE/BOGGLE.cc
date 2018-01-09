#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

#define TEST_SIZE       1000
#define __MESSAGE(s)    \
    std::cout << s << std::endl;

#define __TIMEMEASURE(func, ...)      \
    ts = std::chrono::high_resolution_clock::now();   \
    std::cout << func(__VA_ARGS__) << std::endl;  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   

#define __TIMEMEASURE_NOSTDOUT(func, ...)      \
    ts = std::chrono::high_resolution_clock::now();   \
    func(__VA_ARGS__);  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   

bool hasWord(int y, int x, const std::string& word, std::vector<std::string> board)
{
    /* out of range */
    if(y < 0 || x < 0 || y >= 5 || x >= 5)
        return false;

    /* Not matched word */
    if(board[y][x] != word[0])
        return false;

    if(word.size() == 1){
        std::cout << "At point (x, y) = " << "(" << x << ", " << y << ")" << std::endl;
        return true;
    }

    for(int dx = -1; dx <= 1; ++dx){
        for(int dy = -1; dy <= 1; ++dy){
            std::cout << "Finding (x, y) = " << "(" << x + dx << ", " << y + dy << ")" << std::endl;
            if((dx || dy) && hasWord(y + dy, x + dx, word.substr(1), board)){
                std::cout << "At point (x, y) = " << "(" << x << ", " << y << ")" << std::endl;
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    std::vector<std::string> board;

    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

    board.push_back("URLPM");
    board.push_back("XPRET");
    board.push_back("GIAET");
    board.push_back("XTNZY");
    board.push_back("HOQRS");

    __TIMEMEASURE_NOSTDOUT(hasWord, 1, 1, "PRETTY", board);
//    __MESSAGE("Assertion Testing....");
//    assert(hasWord(1, 1, "PRETTY", board));
//    assert(hasWord(2, 0, "GIRL", board));
//    assert(hasWord(4, 0, "HONEY", board));
//    assert(!hasWord(1, 1, "PRETTYMY", board));
//    assert(!hasWord(2, 0, "GIRAL", board));
//    __MESSAGE("Assertion Testing Finished!");

	return 0;
}
