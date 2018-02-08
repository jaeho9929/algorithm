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

class CantorDust{
    
    public:
        string getstring(int T){
            if(T == 0)  return "X";
            string c = getstring(T - 1);
            return c + string(c.size(), ' ') + c;
        }

        int occurrencesNumber(vector<string> pattern, int time)
        {
            int M = pattern.size(), N = pattern[0].size();
            bool a[M], b[N];
            for(int i = 0; i < M; i++)  a[i] = false;
            for(int i = 0; i < N; i++)  b[i] = false;
            string C = getstring(time);

            int L = C.size();
            int x, y, k;
            int p = 0, q = 0;
            bool flag = false;
            for(x = 0; x < M; ++x){
                for(y = 0; y < N; ++y){
                    if(pattern[x][y] == 'X')
                        a[x] = b[y] = flag = true;
                }
            }
            for(x = 0; x < M; ++x){
                for(y = 0; y < N; ++y){
                    if((pattern[x][y] == 'X') != (a[x] && b[y]))
                        return 0;
                }
            }

            for(k = 0; k + M <= L; ++k){
                for(x = 0; x < M; ++x)
                    if((C[k + x] == 'X') != a[x])
                        break;
                if(x == M)  ++p;
            }

            for(k = 0; k + N <= L; ++k){
                for(y = 0; y < N; ++y)
                    if((C[k + y] == 'X')    != b[y])    break;
                if(y == N)  ++q;
            }

            if(flag)    return (p*q);
            else    return (p*(L - N + 1) + (L - M + 1)*q -p*q);
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    CantorDust solver;

    int cc;
    int row, col;
    char mark;
    string patternLine = "";
    vector<string> pattern;
    int time;
    
    cin >> cc;
    while(cc--){
        cin >> col >> row;
        for(int i = 0; i < col; i++){
            for(int j = 0; j < row; j++){
                cin >> mark;
                patternLine += mark;
            }
            pattern.push_back(patternLine);
            patternLine = "";
        }
        cin >> time;
        cout << "CASE \"" << cc << "\"" << endl;
        __TIMEMEASURE(solver.occurrencesNumber, pattern, time);
        pattern.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
