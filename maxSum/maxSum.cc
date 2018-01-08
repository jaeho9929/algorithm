#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
#include <limits>

#define TEST_SIZE       1000
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
    std::cout << func(arg1, arg2, arg3) << std::endl;  \
    te = std::chrono::high_resolution_clock::now();   \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();    \
    std::cout << "Execution time of "<< #func " " << "; " << duration << "us" << std::endl;   

const int MIN = std::numeric_limits<int>::min();

int maxSum1(const std::vector<int>& A)
{
	int N = A.size(), ret = MIN;
	for(int i = 0; i < N; ++i){
		//std::cout << "Loop I :" << i << std::endl;
		for(int j = i; j < N; ++j){
			//std::cout << "====Loop J :" << j << std::endl;
			int sum = 0;
			for(int k = i; k <= j; ++k){
				sum += A[k];
			}
			ret = std::max(ret, sum);
		}
	}
	return ret;
}

int maxSum2(const std::vector<int>& A)
{
	int N = A.size(), ret = MIN;
	for(int i = 0; i < N; ++i){
		//std::cout << "Loop I :" << i << std::endl;
		int sum = 0;
		for(int j = i; j < N; ++j){
			//std::cout << "====Loop J :" << j << std::endl;
			sum += A[j];
			ret = std::max(ret,sum);
		}
	}
	return ret;
}

int maxSum3(const std::vector<int>& A, int lo, int hi)
{
	if(lo == hi)
		return A[lo];

	int mid = (lo + hi) / 2;

	int left = MIN, right = MIN, sum = 0;

	for(int i = mid; i >= lo; --i){
		sum += A[i];
		left = std::max(left, sum);
	}

	sum = 0;

	for(int j = mid + 1; j <= hi; ++j){
		sum += A[j];
		right = std::max(right, sum);
	}

	int single = std::max(maxSum3(A, lo, mid), maxSum3(A, mid+1, hi));

	return std::max(left + right, single);
}

int maxSum4(const std::vector<int>& A)
{
	int N = A.size(), ret = MIN, psum = 0;

	for(int i = 0; i < N; ++i){
		psum = std::max(psum , 0) + A[i];
		ret = std::max(psum, ret);
	}

	return ret;
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
    std::uniform_int_distribution<int> range(-10, 10);

    __MESSAGE("Generating Test Case ; ");
    for(int i = 0; i < TEST_SIZE; i++){
        testCase.push_back(range(rnd));
//        std::cout << testCase[i] << ", ";
    }
    std::cout << std::endl;
    __MESSAGE("Generation End");
    std::cout << std::endl;
	__TIMEMEASURE(maxSum1, testCase);
	__TIMEMEASURE(maxSum2, testCase);
	__TIMEMEASURE3(maxSum3, testCase, 0, testCase.size() - 1);
	__TIMEMEASURE(maxSum4, testCase);
	
	return 0;
}
