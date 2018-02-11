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

long long dp[9999999];
long long dp2[9999999];
map<long long, long long> m;
const int MAX = 1000000;
long long dp3[9999999];
class InfinitySequence2{
    
    public:
        long long calc(long n, int p, int q, int x, int y)
        {
            return recursion(n, p, q, x, y);
        }

        long long recursion(long n, int p, int q, int x, int y)
        {
            if(n <= 0)  return 1;
            return recursion(n / p - x, p, q, x, y) + recursion(n / q - y, p, q, x, y);
        }

        long long calc2(long long n, int p, int q, int x, int y)
        {
            int i;
            dp[0] = 1;
            for(i = 1; i <= n; i++){
                dp[i] = 0;
                long long nexta = i / p - x;
                long long nextb = i / q - y;
                if(nexta <= 0)  dp[i]++;
                else    dp[i] += dp[nexta];
                if(nextb <= 0)  dp[i]++;
                else    dp[i] += dp[nextb];
            }
            return dp[n];
        }

        long long calc3(long n, int p, int q, int x, int y)
        {
            return recursion2(n, p, q, x, y);
        }

        long long recursion2(long n, int p, int q, int x, int y)
        {
            if(n <= 0)  return 1;
            if(dp2[n] != 0) return dp2[n];
            return dp2[n] = (recursion2(n / p - x, p, q, x, y) + recursion2(n / q - y, p, q, x ,y));
        }

        long long calc4(long n, int p, int q, int x ,int y)
        {
            return recursion3(n, p, q, x, y);
        }
        
        long long recursion3(long n, int p, int q, int x, int y)
        {
            if(n <= 0)  return 1;
            if(m[n] != 0)   return m[n];
            return m[n] = (recursion3(n / p - x, p, q, x, y) + recursion3(n / q - y, p, q, x, y));
        }

        long long calc5(long n, int p, int q, int x, int y)
        {
            return recursion4(n, p, q, x, y);
        }

        long long recursion4(long n, int p, int q, int x, int y)
        {
            if(n <= 0)  return 1;
            if(n < MAX){
                if(dp3[n] != 0) return dp[n];
                else    return dp[n] = recursion4(n / p - x, p, q, x, y) + recursion4(n / q - y, p, q, x, y);
            }
            return recursion4(n / p - x, p, q, x, y) + recursion4(n / q - y , p, q, x, y);
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    InfinitySequence2 solver;

    int cc;
    long n;
    int p, q, x, y;
    
    cin >> cc;
    while(cc--){
        cin >> n;
        cin >> p;
        cin >> q;
        cin >> x;
        cin >>  y;
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.calc, n, p, q, x, y);
        __TIMEMEASURE(solver.calc2, n, p, q, x, y);
        __TIMEMEASURE(solver.calc3, n, p, q, x, y);
        __TIMEMEASURE(solver.calc4, n, p, q, x, y);
        __TIMEMEASURE(solver.calc5, n, p, q, x, y);
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
