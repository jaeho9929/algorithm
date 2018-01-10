#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

#define TEST_SIZE       1000

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

int countPairings1(bool areFriends[10][10], bool taken[10], int n, int m)
{
    int firstFree = -1;
    for(int i = 0; i < n; ++i){
        if(!taken[i]){
            firstFree = i;
            break;
        }
    }

    if(firstFree == -1)
        return 1;

    int ret = 0;
    for(int pairWith = (firstFree+1); pairWith < n; pairWith++){
        if(!taken[pairWith] && areFriends[firstFree][pairWith]){
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings1(areFriends, taken, n, m);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
    return ret;
}

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    int cases, n, m;
    bool areFriends[10][10];
    bool taken[10];             // True if n-th student found the pair

    cin >> cases;

    while(cases--){
        cin >> n >> m;
        assert(n <= 10);
        memset(areFriends, 0, sizeof(areFriends));
        for(int i = 0; i < m; ++i){
            int a, b;
            cin >> a >> b;
            assert(0 <= a && a < n && 0 <= b && b <= n);
            assert(!areFriends[a][b]);
            areFriends[a][b] = areFriends[b][a] = true;
        }
//        cout << "#### areFriends allocation Table" << endl;
//        for(int j = 0; j < n; j++){
//            for(int k = 0; k < n; k++){
//                if(areFriends[j][k] == true){
//                    cout << " *";
//                }else{
//                    cout << "  ";
//                }
//            }
//            cout << endl;
//        }
        memset(taken, 0, sizeof(taken));
        __TIMEMEASURE(countPairings1, areFriends, taken, n, m);
        cout << endl;
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
