#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

#define TEST_SIZE       1000

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

// Assume that previous blocks are already filled.
// Then, we can generate only four case using blocks.
const int coverType[4][3][2] = {
    {{0,0}, {1,0}, {0,1}},
    {{0,0}, {0,1}, {1,1}},
    {{0,0}, {1,0}, {1,1}},
    {{0,0}, {1,0}, {1,-1}}
    };

bool set(vector<vector<int>>& board, int y, int x, int type, int delta)
{
    bool ok = true;
    for(int i = 0; i < 3; ++i){
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()){       // exceed boundary
            ok = false;
        }else if((board[ny][nx] += delta) > 1){                                    // cover again case
            ok = false;
        }
    }

    return ok;
}

int cover(vector<vector<int>>& board)
{
    int y = -1, x = -1;
    for(int i = 0; i < board.size(); ++i){              // check height coordinate of board
        for(int j = 0; j < board[i].size(); ++j){       // check width coordinate of board
            if(board[i][j] == 0){
                y = i;
                x = j;
                break;
            }
        }
            if(y != -1) break;  // found the first empty block.
    }

    // base case, nothing to find the empty blocks.
    if((y == -1) && (x == -1)) return 1;

    int ret = 0;
    for(int type = 0; type < 4; ++type){
        if(set(board, y, x, type, 1)){
            ret += cover(board);        // recursive func.
        }
        set(board, y, x, type, -1);
    }
    return ret;
}

int main(void)
{
    //std::random_device rn;

    std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();

    int cases, height, width;

    cin >> cases;

    while(cases--){
        cout << "The Case : " << cases <<endl;
        cin >> height >> width;
        assert(1 <= height && height <= 20);
        assert(1 <= width && width <= 20);
        cout << "H x W : " << height << " X " << width << endl;
        vector<vector<int>> board(height, vector<int>(width, 0));           // init vector width with 0
        int whites = 0;
        for(int i = 0; i < (height); i++){
            string s;
            cin >> s;
            cout << s << endl;
            for(int j = 0; j < (width); j++){
                if(s[j] == '#')
                    board[i][j] = 1;
            }
            whites += count(board[i].begin(), board[i].end(), 0);           // check number of white blocks
        }
        assert(whites <= 50);
        cout << "Number Of White Block = " << whites << endl;
        cout << "Result : ";
        __TIMEMEASURE(cover, board);
        cout << endl;
    }

//    std::mt19937_64 rnd(rn());
//    std::mt19937 rnd(rn());
//    std::uniform_int_distribution<int> range(-10, 10);

	return 0;
}
