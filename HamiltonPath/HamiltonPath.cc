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

bool visited[50] = {false};

class HamiltonPath{

    vector<string> roads;

    public:
        int countPaths(vector<string> roads)
        {
            int group = 0, free = 0;
            int connect[50] = {0};

            long long sum = 1;

            this->roads = roads;

            for(int i = 0; i < roads.size(); i++){
                int y = 0;
                for(int j = 0; j < roads[i].size(); j++){
                    if(roads[i].substr(j,1) == "Y"){
                        if(2 < ++y) return 0;
                    }
                }
                connect[i] = y;
            }

            for(int i = 0; i < roads.size(); i++){
                if(connect[i] == 0){
                    visited[i] = true;
                    free++;
                }else if(connect[i] == 1 && !visited[i]){
                    group++;
                    dfs(i);
                }
            }

            for(int i = 0; i < roads.size(); i++){
                if(!visited[i]) return 0;
            }
            for(int i = 0; i < group+free; i++){
                sum = sum*(i+1) % 1000000007;
            }
            for(int i = 0; i < group; i++){
                sum = sum*2 % 1000000007;
            }

            for(int i = 0; i < 50; i++){
                connect[i] = 0;
                visited[i] = false;
            }
            roads.clear();

            return (int)sum;
        }

        void dfs(int city)
        {
            visited[city] = true;
            for(int i = 0; i < roads[city].size(); i++){
                if(roads[city].substr(i,1) == "Y" && !visited[i])   dfs(i);
            }
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    HamiltonPath solver;
    
    int cc;
    int nodes;
    string tmp;
    vector<string> roads;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> nodes;
        for(int i = 0; i < nodes; i++){
            cin >> tmp;
            roads.push_back(tmp);
        }
        __TIMEMEASURE(solver.countPaths, roads);
        roads.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
