#include <iostream>

#define MAX_N 101
#define MAX_M 101
#define DIR_NUM 4
using namespace std;

int n, m;
char grid[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int x, int y){
    return InRange(x, y) && !visited[x][y];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;

    int dx[DIR_NUM] = {0, 1, 0, -1}, dy[DIR_NUM] = {1, 0, -1, 0};
    int x = 0, y = 0, dir = 0;
    grid[x][y] = 'A';
    visited[x][y] = true;

    for(int i=1; i<n*m; i++){
        int new_x = x + dx[dir];
        int new_y = y + dy[dir];
        if(!CanGo(new_x, new_y)){
            dir = (dir + 1) % 4;
        }
        x = x + dx[dir];
        y = y + dy[dir];
        grid[x][y] = i % 26 + 'A';
        visited[x][y] = true;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}