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

class InterestingParty{
    public:
        int bestInvitation(vector<string> firstHobby, vector<string> secondHobby){
            int checkerSize = firstHobby.size() * 2;
            vector<string> checker(checkerSize, "*");
            string key;
            int returns = 0;
            int counts = 0;

            checker = firstHobby;
            checker.insert(checker.end(), secondHobby.begin(), secondHobby.end());

            for(int i = 0; i < checker.size(); i++){
                counts = 0;
                key = checker[i];
                for(int j = i; j < checker.size(); j++){
                    if(key == checker[j]){
                        counts++;
                    }
                }
                returns = max(returns, counts);
            }
            checker.clear();

            return returns;
        }

       int bestInvitation2(vector<string> firstHobby, vector<string> secondHobby){
            int checkerSize = firstHobby.size() * 2;
            vector<string> checker(checkerSize, "*");
            string key;
            int returns = 0;
            int counts = 0;

            checker = firstHobby;
            checker.insert(checker.end(), secondHobby.begin(), secondHobby.end());

            for(int i = 0; i < checker.size(); i++){
                counts = 0;
                key = checker[i];
                for(int j = i + 1; j < checker.size(); j++){
                    if(key == checker[j]){
                        counts++;
                    }
                }
                returns = max(returns, counts);
            }
            checker.clear();

            return returns + 1;
        }
       
       int bestInvitation3(vector<string> firstHobby, vector<string> secondHobby){
           int i, j;
           int ans = 0;

           for(i = 0; i < firstHobby.size(); i++){
               int f = 0;
               int s = 0;
               for(j = 0; j < firstHobby.size(); j++){
                   if(firstHobby[i] == firstHobby[j])   f++;
                   if(firstHobby[i] == secondHobby[j])  f++;
                   if(secondHobby[i] == firstHobby[j])  s++;
                   if(secondHobby[i] == secondHobby[j]) s++;
               }
               ans = max(f, ans);
               ans = max(s, ans);
           }

           return ans;
       }

       int bestInvitation4(vector<string> firstHobby, vector<string> secondHobby){
            map<string, int> dic;

            for(int i = 0; i < firstHobby.size(); i++){
                dic[firstHobby[i]] = 0;
                dic[secondHobby[i]] = 0;
            }

            for(int i = 0; i < firstHobby.size(); i++){
                dic[firstHobby[i]]++;
                dic[secondHobby[i]]++;
            }

            int ans = 0;
            map<string, int>::iterator it;

            for(it = dic.begin(); it != dic.end(); it++){
                ans = max(ans, it->second);
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

    InterestingParty solver;

    int cc;
    string tmp;
    int firstCnt, secondCnt;
    vector<string> firstHobby, secondHobby;
    int returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> firstCnt;
        for(int i = 0; i < firstCnt; i++){
            cin >> tmp;
            firstHobby.push_back(tmp);
        }
        cin >> secondCnt;
        for(int i = 0; i < secondCnt; i++){
            cin >> tmp;
            secondHobby.push_back(tmp);
        }
 
        __TIMEMEASURE_WITHRETURN(returns, solver.bestInvitation, firstHobby, secondHobby);
        __TIMEMEASURE_WITHRETURN(returns, solver.bestInvitation2, firstHobby, secondHobby);
        __TIMEMEASURE_WITHRETURN(returns, solver.bestInvitation3, firstHobby, secondHobby);
        __TIMEMEASURE_WITHRETURN(returns, solver.bestInvitation4, firstHobby, secondHobby);
        cout << "CASE \"" << cc << "\"" << endl;
        cout << returns << " ";
        cout << endl;
        firstHobby.clear();
        secondHobby.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
