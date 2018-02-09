#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <cassert>
#include <limits.h>

using namespace std;

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

#define __TIMEMEASURE_WITHRETURN(ret ,func, ...)      \
    ts = std::chrono::high_resolution_clock::now();   \
    ret = func(__VA_ARGS__);  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;

class NotTwo{
    
    public:
        int maxStones(int width, int height)
        {
            vector<vector<int>> board(1005, vector<int>(1005));
            int res = 0;
            int i, j;

            for(i = 2; i < width + 2; i++){
                for(j = 2; j < height + 2; j++){
                    if(board[i - 2][j] == 0 && board[i][j - 2] == 0){
                        res ++;
                        board[i][j] = 1;
                        cout << "o";
                    }else
                        cout << "+";
                }
                cout << endl;
            }
            return res;
        }


        int maxStones2(int width, int height)
        {
            int i, j, res = 0;

            for(i = 0; i < 2; i++){
                for(j = 0; j < 2; j++){
                    res += (((width + i) / 2) * ((height + j) / 2) + 1) / 2;
                }
            }
            return res;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    NotTwo solver;

    int cc;
    int width, height;
    
    cin >> cc;
    while(cc--){
        cin >> width;
        cin >> height;
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.maxStones, width, height);
        __TIMEMEASURE(solver.maxStones2, width, height);
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
