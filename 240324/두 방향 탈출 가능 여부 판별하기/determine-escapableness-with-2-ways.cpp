#include <iostream>

#define MAX 101
using namespace std;

int n, m;
int grid[MAX][MAX];
bool visited[MAX][MAX];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

void DFS(int x, int y){
    int dx[2] = {0, 1}, dy[2] = {1, 0};

    for(int i=0; i<2; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && grid[new_x][new_y]){
            visited[new_x][new_y] = true;
            DFS(new_x, new_y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> grid[i][j];
        }
    }
    visited[0][0] = true;
    DFS(0, 0);
    if(visited[n-1][m-1]) cout << "1";
    else cout << "0";
    return 0;
}