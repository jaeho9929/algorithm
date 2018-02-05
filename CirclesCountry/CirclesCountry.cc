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

class CirclesCountry{
    public:
        int leastBorders(vector<int> X, vector<int> Y, vector<int> R, int x1, int y1, int x2, int y2)
        {
            int num = 0;

            for(int i = 0; i < X.size(); i++){
                if(inside(X[i], Y[i], x1, y1, R[i]) != inside(X[i], Y[i], x2, y2, R[i]))
                    num++;
            }
            return num;
        }

        bool inside(int x1, int y1, int x2, int y2, int r){
            return (x1 - x2) * (x1 - x2) + (y1 - y2)*(y1 - y2) <= r*r;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    CirclesCountry solver;
    
    int cc;
    int countries;
    int tmp;
    vector<int> X, Y, R;
    int x1, y1, x2, y2;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> countries;
        for(int i = 0; i < countries; i++){
            cin >> tmp;
            X.push_back(tmp);
        }
        for(int i = 0; i < countries; i++){
            cin >> tmp;
            Y.push_back(tmp);
        }
        for(int i = 0; i < countries; i++){
            cin >> tmp;
            R.push_back(tmp);
        }
        cin >> x1 >> y1 >> x2 >> y2;

        __TIMEMEASURE(solver.leastBorders, X, Y, R, x1, y1, x2, y2);

        X.clear();
        Y.clear();
        R.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
