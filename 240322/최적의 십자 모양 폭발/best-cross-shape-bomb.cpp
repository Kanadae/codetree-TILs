#include <iostream>

#define MAX_N 51
#define DIR_NUM 4
using namespace std;

int N;
int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

void Bomb(int row, int col){
    int power = grid[row][col];
    for(int i=1; i<power; i++){
        if(row-i>=0) grid[row-i][col] = 0;
        if(row+i< N) grid[row+i][col] = 0;
        if(col-i>=0) grid[row][col-i] = 0;
        if(col+i< N) grid[row][col+i] = 0;
    }
}

void Gravity(){
    for(int col=0; col<N; col++){
        int idx = N-1;
        for(int row=N-1; row>=0; row--){
            if(grid[row][col] != 0) temp[idx--][col] = grid[row][col];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = temp[i][j];
            temp[i][j] = 0;
        }
    }
}

int MaxPair(){
    int pair = 0;
    int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int dir=0; dir<DIR_NUM; dir++){
                int new_x = i + dx[dir];
                int new_y = j + dy[dir];
                if(InRange(new_x, new_y) && !visited[new_x][new_y]){
                    if(grid[i][j] == grid[new_x][new_y] && grid[i][j] != 0) pair++;
                }
            }
            visited[i][j] = true;
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            visited[i][j] = false;
        }
    }
    return pair;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
        }
    }

    int ans = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            Bomb(i, j);
            Gravity();
            ans = max(ans, MaxPair());
        }
    }
    cout << ans;
    return 0;
}