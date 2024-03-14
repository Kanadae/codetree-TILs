#include <iostream>

#define MAX 101
#define DIR_NUM 4
using namespace std;

int n, m;
int grid[MAX][MAX];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    int x = 0, y = 0, dir = 1;
    grid[x][y] = 1;
    for(int i=2; i<=n*m; i++){
        int new_x = x + dx[dir];
        int new_y = y + dy[dir];
        if(!InRange(new_x, new_y) || grid[new_x][new_y] != 0){
            dir = (dir + 1) % 4;
        }
        x = x + dx[dir], y = y + dy[dir];
        grid[x][y] = i;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}