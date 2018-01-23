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

class KiwiJuiceEasy{
    public:
        vector<int> thePouring(vector<int> capacities,
                                vector<int> bottles,
                                vector<int> fromId, vector<int> toId)
        {
            for(int i = 0; i < toId.size(); i++){
                if(bottles[toId[i]] == capacities[toId[i]]) continue;
                if((bottles[fromId[i]] + bottles[toId[i]]) > capacities[toId[i]]){
                    bottles[fromId[i]] -= (capacities[toId[i]] - bottles[toId[i]]);
                    bottles[toId[i]] = capacities[toId[i]];
                }else{
                    bottles[toId[i]] += bottles[fromId[i]];
                    bottles[fromId[i]] = 0;
                }
            }
//            for(int i = 0; i < bottles.size(); i++)
//                cout << bottles[i] << " ";
//            cout << endl;
            return bottles;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    KiwiJuiceEasy solver;

    int cc;
    int tmp;
    int capaCnt, bottleCnt, fromIdCnt, toIdCnt;
    vector<int> capacities, bottles, fromId, toId;
    vector<int> returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> capaCnt;
        for(int i = 0; i < capaCnt; i++){
            cin >> tmp;
            capacities.push_back(tmp);
        }
        cin >> bottleCnt;
        for(int i = 0; i < bottleCnt; i++){
            cin >> tmp;
            bottles.push_back(tmp);
        }
        cin >> fromIdCnt;
        for(int i = 0; i < fromIdCnt; i++){
            cin >> tmp;
            fromId.push_back(tmp);
        }
        cin >> toIdCnt;
        for(int i = 0; i < toIdCnt; i++){
            cin >> tmp;
            toId.push_back(tmp);
        }
        
        //returns = solver.thePouring(capacities, bottles, fromId, toId);
        __TIMEMEASURE_WITHRETURN(returns ,solver.thePouring, capacities, bottles, fromId, toId);
        cout << "CASE \"" << cc << "\"" << endl;
        for(int i = 0; i < returns.size(); i++)
            cout << returns[i] << " ";
        cout << endl;
        capacities.clear();
        bottles.clear();
        fromId.clear();
        toId.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
