#include <iostream>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;

int n, m, r, c;
int grid[MAX_N][MAX_N];
int copy_grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Bomb(int x, int y){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i] * m;
        int new_y = y + dy[i] * m;
        if(InRange(new_x, new_y)){
            copy_grid[new_x][new_y] = 1;
        }
    }
}

void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_grid[i][j] = grid[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]) Bomb(i, j);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = copy_grid[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> r >> c;
    grid[r-1][c-1] = 1;
    for(int t=1; t<=1; t++){
        Simulate();
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]) ans++;
        }
    }
    cout << ans;
    return 0;
}