#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>

#define TEST_SIZE       1000000
#define __MESSAGE(s)    \
    std::cout << s << std::endl;

#define __TIMEMEASURE(ret, func, arg1, arg2)      \
    ts = std::chrono::high_resolution_clock::now();   \
	ret = func(arg1, arg2);	\
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   \


std::vector<double> movingAverage1(const std::vector<double>& A, int M)
{
	std::vector<double> ret;
	int N = A.size();

	for(int i = M-1; i < N; ++i){
		double partialSum = 0;
		for(int j = 0; j < M; ++j){
			partialSum += A[i-j];
		}
		ret.push_back(partialSum / M);
	}
	return ret;
}

std::vector<double> movingAverage2(const std::vector<double>& A, int M)
{
	std::vector<double> ret;
	int N = A.size();
	double partialSum = 0;

	for(int i = 0; i < M-1; ++i){
		partialSum += A[i];
	}
	for(int i = M-1; i < N; ++i){
		partialSum += A[i];
		ret.push_back(partialSum / M);
		partialSum -= A[i-M+1];
	}
	return ret;
}

int main(void)
{
    std::vector<double> testCase;
	std::vector<double> resultCase;
    testCase.reserve(TEST_SIZE);
	int graph;

    std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    //std::mt19937_64 rnd(rn());
    std::mt19937 rnd(rn());
    std::uniform_real_distribution<double> range(60.0, 120.0);

    __MESSAGE("Generating Test Case ; ");
    for(int i = 0; i < TEST_SIZE; i++){
        testCase.push_back(range(rnd));
        //std::cout << testCase[i] << ", ";
    }
    __MESSAGE("Generation End");

//	for(int i = 0; i < testCase.size(); i++){
//		std::cout << testCase[i];;
//		for(int j = 0; j < (int)(testCase[i] / 2); j++){
//			std::cout << "#";
//		}
//		std::cout << std::endl;
//    }
//
//	std::cout<<std::endl;

	__TIMEMEASURE(resultCase, movingAverage1, testCase, 20); 
	__TIMEMEASURE(resultCase, movingAverage2, testCase, 20); 

//	for(int i = 0; i < resultCase.size(); i++){
//		std::cout << resultCase[i];;
//		for(int j = 0; j < (int)(resultCase[i] / 2); j++){
//			std::cout << "#";
//		}
//		std::cout << std::endl;
//    }
	
	return 0;
}
