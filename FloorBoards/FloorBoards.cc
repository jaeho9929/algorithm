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

class FloorBoards{
    
    public:
        int addLine(int prev, int now, int field, int n)
        {
            int i;
            int res = 0;
            bool flag = false;
            for(i = 0; i < n; i++){
                if(((now >> i) & 1) == 1){
                    if(((prev >> i) & 1) != 1)  res++;
                    flag = false;
                }
                else{
                    if(((field >> i) & 1) == 1) flag = false;
                    else{
                        if(!flag)   res++;
                        flag = true;
                    }
                }
            }
            return res;
        }

        int layout(vector<string> room)
        {
            int i, j, k;
            int len = room[0].size();
            int MAX = 99999;
            int dp[room.size() + 1][1 << len];
            for(i = 0; i <= room.size(); i++){
                for(j = 0; j < (1 << len); j++) dp[i][j] = MAX;
            }
            dp[0][0] = 0;

            for(i = 0; i < room.size(); i++){
                int field = 0;
                for(j = 0; j < len; j++)
                    if(room[i][j] == '#')   field += (1 << j);
                for(j = 0; j < (1 << len); j++){
                    if(dp[i][j] == MAX) continue;
                    for(k = 0; k < (1 << len); k++){
                        if((field & k) != 0)    continue;
                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + addLine(j, k, field, len));
                    }
                }
            }
            int res = MAX;

//            for(i = 0; i < room.size(); i++){
//                for(j = 0; j < (1 << len); j++){
//                    cout << dp[i][j] << " ";
//                }
//                cout << endl;
//            }

            for(i = 0; i < (1 << len); i++){
                //cout << "Index : " << i << endl;
                //cout << "Compare : " << res << " and " << dp[room.size()][i] << endl;
                res = min(res, dp[room.size()][i]);
            }
            return res;
        }

        int layout2(vector<string> room)
        {
            int i, j, k, len = room[0].size();
            int MAX = 99999;
            int dp[1 << len];
            for(i = 0; i < (1 << len); i++) dp[i] = MAX;
            dp[0] = 0;

            for(i = 0; i < room.size(); i++){
                for(j = 0; j < room[0].size(); j++){
                    int nextdp[1 << len];
                    for(k = 0; k < (1 << len); k++) nextdp[k] = MAX;
                    for(k = 0; k < (1 << len); k++){
                        if(dp[k] == MAX)    continue;
                        int next0 = (k << 1) & ((1 << len) - 1);
                        int next1 = next0 + 1;
                        if(room[i][j] == '#'){
                            nextdp[next0] = min(nextdp[next0], dp[k]);
                        }else{
                            if(i != 0 && room[i - 1][j] != '#' && (k >> (len - 1)) % 2 == 1)
                                nextdp[next1] = min(nextdp[next1], dp[k]);
                            else
                                nextdp[next1] = min(nextdp[next1], dp[k] + 1);
                            if(j != 0 && room[i][j-1] != '#' && k % 2 == 0)
                                nextdp[next0] = min(nextdp[next0], dp[k]);
                            else
                                nextdp[next0] = min(nextdp[next0], dp[k] + 1);
                        }
                    }
                    for(k = 0; k < (1 << len); k++) dp[k] = nextdp[k];
                }
            }
            int res = MAX;
            for(i = 0; i < (1 << len); i++) res = min(res, dp[i]);
            return res;
        }
    
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    FloorBoards solver;

    int cc;
    int height, width;
    vector<string> room;
    char tmp;
    string roomLine;
    
    cin >> cc;
    while(cc--){
        cin >> height;
        cin >> width;

        for(int i = 0; i < height; i++){
            roomLine = "";
            for(int j = 0; j < width; j++){
                cin >> tmp;
                roomLine += tmp;
            }
            room.push_back(roomLine);
            roomLine = "";
        }
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.layout, room);
        __TIMEMEASURE(solver.layout2, room);
        room.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
