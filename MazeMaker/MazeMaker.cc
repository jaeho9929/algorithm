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

bool grid[100][100] = {false};
int vx[] = {1, -1, 0, 0};
int vy[] = {0, 0, 1, -1};
double prob[4];

class MazeMaker{

    public:
        int longestPath(vector<string> maze, int startRow, int startCol, vector<int> moveRow, vector<int> moveCol)
        {
            int max = 0;
            int width = maze[0].size();
            int height = maze.size();
            int board[50][50];

            for(int i = 0; i < height; i++){
                for(int j = 0; j < height; j++){
                    board[i][j] = -1;
                }
            }

            board[startRow][startCol] = 0;
            queue<int> queueX;
            queue<int> queueY;
            queueX.push(startCol);
            queueY.push(startRow);

            while(queueX.size() > 0){
                int x = queueX.front();
                int y = queueY.front();
            }
            
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    MazeMaker solver;
    int cc;
    vector<string> maze;
    int mazeCnt;
    string mazeLine;
    int startCol, startRow;
    int moveRCnt, moveCCnt;
    int moveCmd;
    vector<int> moveRow, moveCol;
//    double returns;

    cin >> cc;
    while(cc--){
        /* get test parameters */
        cin >> mazeCnt;
        for(int i = 0; i < mazeCnt; i++){
            cin >> mazeLine;
            maze.push_back(mazeLine);
        }
        cin >> startRow >> startCol;
        cin >> moveRCnt;
        for(int i = 0; i < moveRCnt; i++){
            cin >> moveCmd;
            moveRow.push_back(moveCmd);
        }
        cin >> moveCCnt;
        for(int i = 0; i < moveCCnt; i++){
            cin >> moveCmd;
            moveCol.push_back(moveCmd);
        }

        cout << "CASE \"" << cc << "\"" << endl;
        //__TIMEMEASURE(solver.getProbability, n, east, west, south, north);
 
//        cout << "CASE \"" << cc << "\"" << endl;
//        cout << returns << endl;
//        for(int i = 0; i < returns.size(); i++)
//            cout << returns[i] << " ";
//        cout << endl;
        maze.clear();
        moveRow.clear();
        moveCol.clear();
   }
//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
