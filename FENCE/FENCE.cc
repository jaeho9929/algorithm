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

class FENCE{

    public:
        int exahustiveSearch(vector<int> fences)
        {
            int ret = 0;
            int area = 0;
            int N = fences.size();

            for(int i = 0; i < N; i++){
                int width = 1;
                int height = fences[i];
                for(int j = i - 1; j > 0; j--){
                    //cout << "FENCE L = " << fences[j] << endl;
                    if(height <= fences[j]) width++;
                    else    break;
                }
                for(int k = i + 1; k < N; ++k){
                    if(height <= fences[k]) width++;
                    else    break;
                }
                //cout << "H : " << height;
                //cout << " W : " << width << endl;

                area = width * height;
                ret = max(ret, area);
            }

            return ret;
        }

        int binarySearch(vector<int> fences, int left, int right)
        {
            if(left == right)   return fences[left];
            int mid = (left + right) / 2;
            //cout << "LEFT : " << left << " RIGHT : " << right << endl;
            //cout << "MID NUMBER : " << mid << endl;

            int ret = max(binarySearch(fences, left, mid), binarySearch(fences, mid + 1, right));
            int lo = mid, hi = mid + 1;
            int height = min(fences[lo], fences[hi]);
            ret = max(ret, height * 2);

            while(left < lo || hi < right){
                //cout << "LOW : " << lo << " HIGH : " << hi << endl;
                if(hi < right && (lo == left || fences[lo - 1] < fences[hi + 1])){
                    ++hi;
                    height = min(height, fences[hi]);
                }else{
                    --lo;
                    height = min(height, fences[lo]);
                }
                ret = max(ret, height * (hi - lo + 1));
                //cout << "RETURN VALUE : " << ret << endl;
            }
            return ret;
        }
        
};

int main(void)
{
    //std::random_device rn;
    FENCE solver;
    
    int cc;
    int stickCnt;
    int fence;
    vector<int> fences;
    int result;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    cin >> cc;
    while(cc--){
        cin >> stickCnt;
        for(int i = 0; i < stickCnt; i++){
            cin >> fence;
            fences.push_back(fence);
        }
        __TIMEMEASURE_WITHRETURN(result, solver.exahustiveSearch, fences);
        __TIMEMEASURE_WITHRETURN(result, solver.binarySearch, fences, 0, fences.size());
        cout << result << endl;
        fences.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10)

	return 0;
}
