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

vector<size_t> memo(100, 0);

size_t fib(int n)
{
    if(n < 1)   return 0;
    if(n == 1)  return 1;
    if(n == 2)  return 1;

    return fib(n-1) + fib(n-2);
}

size_t fastfib(int n)
{
    if(n < 1)   return 0;
    if(memo[n] == 0)    memo[n] = fastfib(n-1)+ fastfib(n-2);
    else    return memo[n];
}

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    int cc, n;
    memo[0] = 0;
    memo[1] = 1;
    memo[2] = 1;

    cin >> cc;
    while(cc--){
        cin >> n;
        __TIMEMEASURE(fib, n);
        __TIMEMEASURE(fastfib, n);
    }
    
//    for(int i = 0; i < n; i++)
//        cout << memo[i] << endl;
    
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
