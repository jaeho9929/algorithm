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

class FriendScore{
    public:
        int highestScore(vector<string> friends)
        {
            int friendsCnt = 0;
            int ans = 0;

            for(int i = 0; i < friends.size(); i++){
                friendsCnt = 0;
                for(int j = 0; j < friends.size(); j++){
                    if(friends[i][j] == 'Y'){
                        friendsCnt++;
                    }else if(i != j){   // friends[i][j] == 'N' and i != j
                        for(int k = 0; k < friends.size(); k++){
                            if((friends[j][k] == 'Y') && (friends[i][k] == 'Y')){
                                friendsCnt++;
                                break;
                            }
                        }
                    }
                }
                ans = max(friendsCnt, ans);
            }

            return ans;
        }

        int highestScore2(vector<string> friends)
        {
            int ans = 0;
            int n = friends[0].length();

            for(int i = 0; i < n; i++){
                int cnt = 0;

                for(int j = 0; j < n; j++){
                    if(i == j)  continue;
                    if(friends[i][j] == 'Y'){
                        cnt++;
                    }else{
                        for(int k = 0; k < n; k++){
                            if((friends[j][k] == 'Y') && (friends[k][i] == 'Y')){
                                cnt++;
                                break;
                            }
                        }
                    }
                }
                ans = max(cnt, ans);
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

    FriendScore solver;

    int cc;
    int friendsCnt;
    vector<string> friends;
    string tmp;
    int returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> friendsCnt;
        for(int i = 0; i < friendsCnt; i++){
            cin >> tmp;
            friends.push_back(tmp);
        }
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.highestScore, friends);
        __TIMEMEASURE(solver.highestScore2, friends);
 
//        cout << "CASE \"" << cc << "\"" << endl;
//        cout << returns << endl;
//        for(int i = 0; i < returns.size(); i++)
//            cout << returns[i] << " ";
//        cout << endl;
        friends.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
