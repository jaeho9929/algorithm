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

class BatchSystem{
    public:
        vector<int> schedule(vector<int> duration, vector<string> user)
        {
            int N = duration.size();

            map<string, long long> jobTime;
            for(int n = 0; n < N; n++)
                jobTime[user[n]] += duration[n];

            vector<bool> done(N);
            vector<int> ans;
            while(ans.size() < N){
                string next;
                for(int n = 0; n < N; n++){
                    if(!done[n] && (next.empty() || jobTime[user[n]] < jobTime[next]))
                        next = user[n];
                }
                for(int n = 0; n < N; n++){
                    if(user[n] == next){
                        done[n] = true;
                        ans.push_back(n);
                    }
                }
            }
            return ans;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();
    
    int cc;
    vector<int> waitDuration;
    int userCnt;
    int durationInput;
    string userInput;
    vector<string> user;
    vector<int> returns; 

    BatchSystem solver;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> userCnt;
        for(int i = 0; i < userCnt; i++){
            cin >> durationInput;
            waitDuration.push_back(durationInput);
        }
        for(int i = 0; i < userCnt; i++){
            cin >> userInput;
            user.push_back(userInput);
        }
        
        __TIMEMEASURE_WITHRETURN(returns, solver.schedule, waitDuration, user);
        
        for(int i = 0; i < returns.size(); i++){
            cout << returns[i] << endl;
        }
        waitDuration.clear();
        user.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
