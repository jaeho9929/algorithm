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

long long ways[100][100][55] = {0};
int dx[] = {1, 1, 1, 0, -1, -1, -1, 0, 2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 0, -1, -1, -1, 0, 1, 1, -1, -2, -2, -1, 1, 2, 2, 1};

class ChessMetric{
    public:
        long long howMany(int size, vector<int> start, vector<int> end, int numMoves)
        {
            int x,y,i,j;
            int sx = start[0], sy = start[1], ex = end[0], ey = end[1];

            ways[sy][sx][0] = 1;

            for(int i = 1; i <= numMoves; i++){
                for(x = 0; x < size; x++){
                    for(y = 0; y < size; y++){
                        for(j = 0; j < 16; j++){
                            int nx = x + dx[j];
                            int ny = y + dy[j];
                            if(nx < 0 || ny < 0 || nx >= size || ny >= size)
                                continue;

                            ways[ny][nx][i] += ways[y][x][i-1];
                        }
                    }
                }
            }
            return ways[ey][ex][numMoves];
        }
};

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();
    
    int cc;
    int boardSize;
    int pos;
    int numMoves;
    vector<int> start, end;

    ChessMetric solver;

    cin >> cc;
    while(cc--){
        cout << "CASE \"" << cc << "\"" << endl;
        cin >> boardSize;
        cin >> pos;
        start.push_back(pos);
        cin >> pos;
        start.push_back(pos);
        cin >> pos;
        end.push_back(pos);
        cin >> pos;
        end.push_back(pos);
        cin >> numMoves;
        //solver.howMany(boardSize, start, end, numMoves);
        __TIMEMEASURE(solver.howMany, boardSize, start, end, numMoves);
        start.clear();
        end.clear();
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                for(int k = 0; k < 55; k++){
                    ways[i][j][k] = 0;
                }
            }
        }
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
