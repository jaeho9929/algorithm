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

bool grid[100][100] = {false};
int vx[] = {1, -1, 0, 0};
int vy[] = {0, 0, 1, -1};
double prob[4];

class CrazyBot{

    public:
        double getProbability(int n, int east, int west, int south, int north)
        {
            prob[0] = east / 100.0;
            prob[1] = west / 100.0;
            prob[2] = south / 100.0;
            prob[3] = north / 100.0;

            return dfs(50, 50, n);
        }

        double dfs(int x, int y, int n)
        {
            if(grid[x][y])  return 0;
            if(n == 0)  return 1;

            grid[x][y] = true;
            double ret = 0;
            for(int i = 0; i < 4; i++){
                ret += dfs(x + vx[i], y + vy[i], n-1) * prob[i];
            }

            grid[x][y] = false;
            return ret;
        }

};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    CrazyBot solver;

    int cc;
    int n;
    int east, west, south, north;
//    double returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> n;
        cin >> east >> west >> south >> north;
        assert((n >= 1) && (n <= 14));
        assert((east >= 0) && (east <= 100));
        assert((west >= 0) && (west <= 100));
        assert((south >= 0) && (south <= 100));
        assert((north >= 0) && (north <= 100));
        assert((east + west + south + north) == 100);
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.getProbability, n, east, west, south, north);
 
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
