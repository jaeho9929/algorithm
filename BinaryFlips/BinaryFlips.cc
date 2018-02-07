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

class BinaryFlips{

    int array[300000];
    int k;
    queue<int> q;

    public:
        int minimalMoves(int A, int B, int K)
        {
            if(A == 0)  return 0;
            if(A + B < K)   return -1;
            int array[A + B + 1];
            for(int i = 0; i <= A + B; i++)     // maximum 2*10^5
                array[i] = -1;
            queue<int> q;
            q.push(A);
            array[A] = 0;

            while(!q.empty()){
                int i = q.front();
                //cout << i << endl;
                q.pop();
                //cout <<"min i and K " << i << " and " << K << endl;
                for(int j = max(0, K - (A+B-i)); j <= min(i, K); j++){
                    int nextzero = i + (K - 2*j);
                    //cout << "Next Zero " << nextzero << endl;
                    if(array[nextzero] == -1){
                        if(nextzero == 0)   return array[i] + 1;
                        array[nextzero] = array[i] + 1;
                        q.push(nextzero);
                    }
                }
            }
            return -1;
        }

        int minimalMoves2(int A, int B, int K)
        {
            if(A == 0)  return 0;
            if(A + B < K)   return -1;
            k = K;
            for(int i = 0; i <= A + B; i++) array[i] = -1;
            q.push(A);
            array[A] = 0;
            while(!q.empty()){
                int i = q.front();
                q.pop();
                check(i, max(0, K - (A + B - i)));
                check(i, min(i, K));
                check(i, min(max((i+1) / 2, K - ((A + B) - i)), K));
                check(i, min(max(i/2, K- ((A+B) - i)), K));
            }
            return array[0];
        }

        void check(int nowzero, int userzero)
        {
            int nextzero = nowzero + k - 2*userzero;
            if(array[nextzero] == -1){
                array[nextzero] = array[nowzero] + 1;
                q.push(nextzero);
            }
        }

        int minimalMoves3(int A, int B, int K)
        {
            if(A == 0)  return 0;
            if(A + B < K)   return -1;
            int minvalue = A, maxvalue = A;
            
            for(int i = 0; i < A + B; i++){
                int nextminvalue, nextmaxvalue;

                if(minvalue <= K && maxvalue >= K){
                    if(minvalue % 2 == K % 2)  return i + 1;
                    else nextminvalue = 1;
                }
                else    nextminvalue = min(abs(K - minvalue), abs(K - maxvalue));
                
                if(minvalue <= (A + B - K) && maxvalue >= (A + B - K)){
                    if((A + B - maxvalue) % 2 == K % 2) nextmaxvalue = A + B;
                    else    nextmaxvalue = A + B -1;
                }else   nextmaxvalue = A + B - min(abs((A + B - K) - minvalue), abs((A + B - K) - maxvalue));
                minvalue = nextminvalue;
                maxvalue = nextmaxvalue;
            }
            return -1;
        }

        int minimalMoves4(int A, int B, int K)
        {
            for(long long i = 0; i <= A + B; i++){
                long long rest = i * K -A;
                long long use = ((i/2) * B + ((i-1)/2)*A)*2;
            if(rest >= 0 && rest % 2 == 0 && rest <= use)
                return (int)i;
            }
            return -1;
        }

        int minimalMoves5(int A, int B, int K)
        {
            if(A == 0)  return 0;
            if(A == K)  return 1;
            if(K >= A + B || ((A % 2 ==1) && (K % 2 == 0))) return -1;

            int ret = (int)1e9;

            if(A % 2 == 0)
            {
                int patternA = (3*A + 2*B -2*K -1) / (A + B - K) / 2;
                int patternB = (A + 2*K -1) / K / 2;
                ret = min(ret, 2*max(patternA, patternB));
            }

            if((K % 2 == 0) || ((A % 2) == 1))
            {
                int patternA = (3*A + 4*B - 3*K -1) / (A + B - K) / 2;
                int patternB = (A + 3*K -1) / K / 2;
                ret = min(ret, 2*max(patternA, patternB) -1);
            }
            return ret;
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    BinaryFlips solver;

    int cc;
    int A, B, K;
    
    cin >> cc;
    while(cc--){
        cin >> A >> B >> K;
        cout << "CASE \"" << cc << "\"" << endl;
//        __TIMEMEASURE(solver.minimalMoves5, A, B, K);
//        __TIMEMEASURE(solver.minimalMoves4, A, B, K);
//        __TIMEMEASURE(solver.minimalMoves3, A, B, K);
//        __TIMEMEASURE(solver.minimalMoves2, A, B, K);
        __TIMEMEASURE(solver.minimalMoves, A, B, K);
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
