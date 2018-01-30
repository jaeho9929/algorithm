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

long long salaries[50] = {0, };

class CorporationSalary{
    public:
        long long totalSalary(vector<string> relations)
        {
            long long total = 0;

            for(int i = 0; i < relations.size(); i++){
                total += getSalary(i, relations);
                //cout << total << endl;
            }
    
            return total;
        }

        long long getSalary(int i, vector<string> relations)
        {
            long long salary = 0;

            if(salaries[i] == 0)
            {
                string relation = relations[i];

                for(int j = 0; j < relation.size(); j++){
                    if(relation[j] == 'Y'){
                        salary += getSalary(j, relations);
                    }
                }
                if(salary == 0)     salary = 1;

                salaries[i] = salary;
            }

            return salaries[i];
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();
    
    int cc;
    int mans;
    string tmp;
    vector<string> relations;

    CorporationSalary solver;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> mans;
        for(int i = 0; i < mans; i++){
            cin >> tmp;
            relations.push_back(tmp);
        }
        __TIMEMEASURE(solver.totalSalary, relations);
        relations.clear();
        for(int i = 0; i < 50; i++)
            salaries[i] = 0;
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
