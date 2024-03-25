#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int ans;
int area;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void DFS(int x, int y, int target){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    visited[x][y] = true;
    area++;
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] == target){
            DFS(new_x, new_y, target);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]) continue;

            int target = grid[i][j];
            DFS(i, j, target);
            if(area > ans) {
                ans = area;
                cnt++;
            }
            area = 0;
        }
    }
    cout << cnt << " " << ans;
    return 0;
}