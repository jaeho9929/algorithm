#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <limits.h>
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

//#define MAX_SIZE 1100000

//char decompressed[MAX_SIZE][MAX_SIZE];

class QUADTREE{

    public:
//        void decompress(string::iterator& it, int y, int x, int size)
//        {
//            char head = *(it++);
//
//            if(head == 'b' || head == 'w'){
//                for(int dy = 0; dy < size; ++dy)
//                    for(int dx = 0; dx < size; ++dx)
//                        decompressed[y+dy][x+dx] = head;
//            }else{
//                int half = size / 2;
//                decompress(it, y, x, half);
//                decompress(it, y, x+half, half);
//                decompress(it, y+half, x, half);
//                decompress(it, y+half, x+half, half);
//            }
//        }
        
        string reverse(string::iterator& it)
        {
            char head = *it;
            ++it;
            if(head == 'b' || head == 'w'){
                return string(1, head);
            }
            string upperLeft = reverse(it);
            string upperRight = reverse(it);
            string lowerLeft = reverse(it);
            string lowerRight = reverse(it);

            return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
        }
        
};

int main(void)
{
    //std::random_device rn;
    QUADTREE solver;
    
    int cc;
    string input;
    string result;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    cin >> cc;
    while(cc--){
        cin >> input;
        string::iterator it = input.begin();
        __TIMEMEASURE_WITHRETURN(result, solver.reverse, it);
        cout << result << endl;
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10)

	return 0;
}
