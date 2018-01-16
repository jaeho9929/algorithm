#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

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

const int INF = 9999;

int clockSwitch[10][16] = {
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
    };

bool areAligned(const vector<int>& clocks)
{
    for(int i = 0; i < 16; i++){
        if((clocks[i] % 4) != 0)
            return false;
    }
    return true;
}

void pushBtn(vector<int>& clocks, int swtch){
    for(int clock = 0; clock < 16; ++ clock)
        if(clockSwitch[swtch][clock] == 1){
            clocks[clock] += 3;
        }
}

int solve(vector<int>& clocks, int swtch){
    if(swtch == 10)
        return areAligned(clocks) ? 0 : INF;
    int ret = INF;
    for(int cnt = 0; cnt < 4; ++cnt){
        ret = min(ret, cnt + solve(clocks, swtch + 1));
        pushBtn(clocks, swtch);
    }
    return ret;
}

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    int cases, clock;
    vector<int> clocks;

    cin >> cases;
    assert(cases <= 30);

    while(cases--){
        for(int i = 0; i < 16; i++){
            cin >> clock;
            assert((clock == 3) | (clock == 6) | (clock == 9) | (clock == 12));
            clocks.push_back(clock);
        }
        int ret = solve(clocks, 0);
        cout << (ret >= INF ? -1 : ret) << endl;
        clocks.clear();
//        __TIMEMEASURE();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
