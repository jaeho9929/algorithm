#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
#include <limits>

#define TEST_SIZE       5         // n
#define SET_SIZE        3           // m

#define __MESSAGE(s)    \
    std::cout << s << std::endl;

#define __TIMEMEASURE(func, arg1)      \
    ts = std::chrono::high_resolution_clock::now();   \
    std::cout << func(arg1) << std::endl;  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   

#define __TIMEMEASURE3(func, arg1, arg2, arg3)      \
    ts = std::chrono::high_resolution_clock::now();   \
    func(arg1, arg2, arg3);  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   

/*

    nCm = n! / (m!*(m-n)!)

*/

void combination1(std::vector<int>& picked, int n, int m)
{

    if(m == 0){
        for(int i = 0; i < picked.size(); ++i)
        {
            std::cout << picked[i] << " ";
        }
        std::cout << std::endl;
    }else{
        int smallest = picked.empty() ? 0 : picked.back() + 1;

        for(int i = smallest; i < n; ++i){
            picked.push_back(i);
            combination1(picked, n, m - 1);
            picked.pop_back();
        }
    }

}


int main(void)
{
    std::vector<int> combSet;

    std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    __TIMEMEASURE3(combination1, combSet, TEST_SIZE, SET_SIZE);
	
	return 0;
}
