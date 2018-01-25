#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
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

class Cryptography{
    public:
        long long encrypt(vector<int> numbers)
        {
            long long returns = 0;
            long long mults = 0;
            long long pi = 1;


            for(int i = 0; i < numbers.size(); i++){
                pi *= numbers[i];
            }
            
            for(int i = 0; i < numbers.size(); i++){
                mults = pi + (pi/numbers[i]);
                returns = max(returns, mults);
            }

            return returns;
        }

        long long encrypt2(vector<int> numbers)
        {
            long long ans = 0;

            for(int i = 0; i < numbers.size(); i++){
                long long temp = 1;
                for(int j = 0; j < numbers.size(); j++){
                    if(i == j)  temp *= (numbers[j] + 1);
                    else    temp *= numbers[j];
                }
                ans = max(ans, temp);
            }

            return ans;
        }

        long long encrypt3(vector<int> numbers)
        {
            long long ret = 1;
            sort(numbers.begin(), numbers.end());
            numbers[0]++;
            for(int i = 0; i < numbers.size(); i++){
                ret *= numbers[i];
            }
            return ret;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    Cryptography solver;

    int cc;
    int tmp;
    int listCnt;
    vector<int> numbers;
    long long returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> listCnt;
        for(int i = 0; i < listCnt; i++){
            cin >> tmp;
            numbers.push_back(tmp);
        }

        __TIMEMEASURE_WITHRETURN(returns , solver.encrypt, numbers);
        __TIMEMEASURE_WITHRETURN(returns , solver.encrypt2, numbers);
        __TIMEMEASURE_WITHRETURN(returns , solver.encrypt3, numbers);
 
        cout << "CASE \"" << cc << "\"" << endl;
        cout << returns << " ";
        cout << endl;
        numbers.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
