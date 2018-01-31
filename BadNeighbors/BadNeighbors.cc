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

class BadNeighbors{
    public:
        int maxDonations(vector<int> donations)
        {
            int i;
            int ans = 0;
            
            int N = donations.size();
            int *dp = new int[N];
            
            for(i = 0; i < N-1; i++){
                dp[i] = donations[i];
                if(i>0) dp[i] = max(dp[i], dp[i-1]);
                if(i>1) dp[i] = max(dp[i], dp[i-2] + donations[i]);
                ans = max(ans, dp[i]);
            }

            for(i = 0; i < N-1; i++){
                dp[i] = donations[i+1];
                if(i>0) dp[i] = max(dp[i], dp[i-1]);
                if(i>1) dp[i] = max(dp[i], dp[i-2] + donations[i+1]);
                ans = max(ans, dp[i]);
            }

            delete [] dp;
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
    int cnt;
    int donation;
    vector<int> donations;

    BadNeighbors solver;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> cnt;
        for(int i = 0; i < cnt; i++){
            cin >> donation;
            donations.push_back(donation);
        }
        __TIMEMEASURE(solver.maxDonations, donations);
        donations.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
