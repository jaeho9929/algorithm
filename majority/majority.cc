#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>

#define TEST_SIZE       10000
#define __MESSAGE(s)    \
    std::cout << s << std::endl;

#define __TIMEMEASURE(func, arg1)      \
    ts = std::chrono::high_resolution_clock::now();   \
    __MESSAGE("majority ;");    \
    std::cout << func(arg1) << std::endl;  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   \

int majority1(const std::vector<int>& A)
{
    int N = A.size();
    int majority = -1, majorityCount = 0;
    int oldmajority = -1;

    for(int i = 0; i < N; ++i){
        int V = A[i], count = 0;
        for(int j = 0; j < N; ++j){
            if(A[j] == V){
                ++count;
            }
        }
        if((count > majorityCount)){
            majorityCount = count;
            majority = V;
        }
        if((count == majorityCount)){   /* for dup. case, highest value ordering */
            if(majority < V){
                majority = V;
            }
        }
    }
    return majority;
}

int majority2(const std::vector<int>& A)
{
    int N = A.size();
    std::vector<int> count(TEST_SIZE + 1, 0);

    for(int i = 0; i < N; ++i){
        count[A[i]]++;
    }

    int majority = 0;
    for(int i = 1; i <= TEST_SIZE; ++i){
        if(count[i] >= count[majority]){ /* for dup. case, highest value ordering */
            majority = i;
        }
    }

    return majority;
}

int majority3(const std::vector<int>& A)
{
    int checker[TEST_SIZE];
    std::fill_n(checker, TEST_SIZE, 0);

    int N = A.size();
    int majority = -1;
    int biggestNum = -1;

    for(int i = 0; i < N ; ++i){
        checker[A[i]] = checker[A[i]] + 1;
    }

    for(int j = 0; j < N; j++){
        if(biggestNum <= checker[j]){
            biggestNum = checker[j];
            majority = j;
        }
    }

    return majority;
}

int main(void)
{
    std::vector<int> testCase;
    testCase.reserve(TEST_SIZE);

    std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    //std::mt19937_64 rnd(rn());
    std::mt19937 rnd(rn());
    std::uniform_int_distribution<int> range(0, TEST_SIZE - 1);

    __MESSAGE("Generating Test Case ; ");
    for(int i = 0; i < TEST_SIZE; i++){
        testCase.push_back(range(rnd));
        //std::cout << testCase[i] << ", ";
    }
    __MESSAGE("Generation End");
    std::cout << std::endl;

    __TIMEMEASURE(majority1, testCase);
    std::cout << std::endl;
    __TIMEMEASURE(majority2, testCase);
    std::cout << std::endl;
    __TIMEMEASURE(majority3, testCase);
    
    return 0;
}
