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

class InterestingDigits{
    public:
        vector<int> digits(int base)
        {
            vector<int> ans;

            for(int i = 2; i < base; i++){
                if(((base - 1) % i) == 0)   ans.push_back(i);
            }

            return ans;
        }

        vector<int> digits2(int base)
        {
            vector<int> ans;

            for(int n = 2; n < base; n++){
                bool ok =true;
                for(int k1 = 0; k1 < base; k1++){
                    for(int k2 = 0; k2 < base; k2++){
                        for(int k3 = 0; k3 < base; k3++){
                            if((k1 + k2*base + k3*base*base) % n == 0 && (k1 + k2 + k3) % n != 0){
                                ok = false;
                                break;
                            }
                        }
                        if(!ok) break;
                    }
                    if(!ok) break;
                }
                if(ok)  ans.push_back(n);
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

    InterestingDigits solver;

    int cc;
    int base;
    vector<int> returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> base;
        __TIMEMEASURE_WITHRETURN(returns , solver.digits, base);
        //__TIMEMEASURE_WITHRETURN(returns , solver.digits2, base);
 
        cout << "CASE \"" << cc << "\"" << endl;
        for(int i = 0; i < returns.size(); i++)
            cout << returns[i] << " ";
        cout << endl;
        returns.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
