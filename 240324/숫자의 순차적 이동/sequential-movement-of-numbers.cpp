#include <iostream>
#include <algorithm>

#define MAX_N 21
#define DIR_NUM 8
using namespace std;

int n, m;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y){
    int dx[DIR_NUM] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[DIR_NUM] = {-1, 0, 1, 1, -1, 0, -1 ,1};
    int maxVal = 0;
    int row = -1, col = -1;

    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y)){
            if(maxVal < grid[new_x][new_y]){
                maxVal = max(maxVal, grid[new_x][new_y]);
                row = new_x, col = new_y;
            }
        }
    }
    swap(grid[row][col], grid[x][y]);
}

void Simulate(int target){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == target){
                Move(i, j);
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    for(int i=0; i<m; i++){
        for(int j=1; j<=n*n; j++){
            Simulate(j);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}