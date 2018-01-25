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

class ThePalindrome{
    public:
        int find(string s)
        {
            int size = s.length();
            int fromleft = 0;
            int fromright = size - 1;
            int ans = s.length();

            for(int i = 0; i < size; i++){
                if((fromleft) == (fromright))
                    return ans;
                if(s[fromleft] != s[fromright]){
                    //cout << "The LEFT" << s[fromleft] << endl;
                    fromleft++;
                    ans++;
                }else if(s[fromleft] == s[fromright]){
                    fromleft++;
                    ans++;
                }else{
                    fromleft++;
                    fromright--;
                }
            }

            return ans;
        }

        int find2(string s)
        {
            for(int i = s.size(); ; i++){
                bool flag = true;
                for(int j = 0; j < s.size(); j++){
                    if((i - j - 1) < s.size() && s[j] != s[i -j -1]){
                        flag = false;
                        break;
                    }
                }
                if(flag)    return i;
            }
        }
        
        
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    ThePalindrome solver;

    int cc;
    string strings;
    int returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> strings;
        //__TIMEMEASURE_WITHRETURN(returns , solver.find2, strings);
        //__TIMEMEASURE_WITHRETURN(returns , solver.find, strings);
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.find, strings);
        __TIMEMEASURE(solver.find2, strings);

//        cout << "CASE \"" << cc << "\"" << endl;
//        cout << returns << endl;
//        for(int i = 0; i < returns.size(); i++)
//            cout << returns[i] << " ";
//        cout << endl;
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
