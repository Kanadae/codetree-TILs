#include <iostream>
#include <queue>

#define MAX 100
#define DIR_NUM 4
using namespace std;

int n, m;
int grid[MAX][MAX];
bool visited[MAX][MAX];
int step[MAX][MAX];

queue<pair<int, int>> q;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

void BFS(){
    while(!q.empty()){
        int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y]){
                visited[new_x][new_y] = true;
                step[new_x][new_y] = step[x][y] + 1;
                q.push(make_pair(new_x, new_y));
            } 
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
    q.push(make_pair(0, 0));
    BFS();
    cout << step[n-1][m-1];
    return 0;
}