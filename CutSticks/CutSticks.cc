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

class CutSticks{
    
    public:
        double maxKth(vector<int> sticks, int C, int K)
        {
            double low = 0;
            double high = 1e9;
            int i, j;
            for(i = 0; i < 100; i++){
                long long count = 0;
                double mid = (low + high) / 2;
                long long cut = 0;
                for(j = 0; j < sticks.size(); j++){
                    long long next = (long)(sticks[j] / mid);
                    cut += max((long long)0, (next - 1));
                    count += next;
                }
                count -= max((long long)0, (cut - C));
                if(count >= K)  low = mid;
                else    high = mid;
            }
            return low;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    CutSticks solver;

    int cc;
    vector<int> sticks;
    int stickCnt;
    int tmp;
    int C;
    int K;
    
    cin >> cc;
    while(cc--){
        cin >> stickCnt;
        for(int i = 0; i < stickCnt; i++){
            cin >> tmp;
            sticks.push_back(tmp);
        }
        cin >> C;
        cin >> K;
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.maxKth, sticks, C, K);
        sticks.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
