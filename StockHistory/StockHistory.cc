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

class StockHistory{
    public:
        int maximumEarnings(int initialInvestment, int monthlyContribution, vector<string> stockPrices)
        {
            int money = initialInvestment;
            int month = stockPrices.size();
            int corp = 1;
            char *s = (char*)stockPrices[0].c_str();
            while(*s++) if(*s == ' ')   corp++;

            int prices[50][999];
            double max = 0, profit = 0;
            double proportion[50] = {0};
            bool buy[50] = {false};

            for(int i = 0; i < month; i++){
                string s = stockPrices[i];
                for(int j = 0; j < corp; j++){
                    int pos = s.find(" ");
                    if(pos == string::npos){
                        prices[i][j] = atoi(s.c_str());
                    }else{
                        prices[i][j] = atoi(s.substr(0, pos).c_str());
                        s = s.substr(pos + 1, s.size());
                    }
                }
            }
            for(int i = month - 2; 0 <= i; i--){
                for(int j = 0; j < corp; j++){
                    double p = 1.0*prices[month - 1][j] / prices[i][j] - 1;
                    if(0 < p && max < p){
                        buy[i] = true;
                        max = p;
                        proportion[i] = p;
                    }
                }
            }

            for(int i = 0; i < month; i++){
                if(buy[i]){
                    profit += money * proportion[i];
                    money = 0;
                }
                money += monthlyContribution;
            }
            return (int)round(profit);
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();
    
    int cc;
    int initialInvestment;
    int monthlyContribution;
    int dataHeight;
    int dataWidth;
    string stockData;
    string dataLine;
    vector<string> stockPrices;

    StockHistory solver;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> initialInvestment;
        cin >> monthlyContribution;
        cin >> dataHeight;
        cin >> dataWidth;
        for(int i = 0; i < dataHeight; i++){
            for(int j = 0; j < dataWidth; j++){
                cin >> stockData;
                dataLine += stockData + " ";
            }
            stockPrices.push_back(dataLine);
            dataLine = "";
        }
        __TIMEMEASURE(solver.maximumEarnings, initialInvestment, monthlyContribution, stockPrices);
        stockPrices.clear();
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
