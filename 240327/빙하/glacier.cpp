#include <iostream>
#include <queue>

#define MAX_N 200
#define MAX_M 200
#define DIR_NUM 4
using namespace std;

int n, m;
int grid[MAX_N][MAX_M];
queue<pair<int, int>> q;
bool visited[MAX_N][MAX_M];

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
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && !grid[new_x][new_y]){
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

void Melt(int x, int y){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && visited[new_x][new_y] && !grid[new_x][new_y]){
            visited[x][y] = true;
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

    q.push(make_pair(0, 0));
    visited[0][0] = true;
    BFS();

    int final_melt = 0;
    int time = 0;
    bool remelt = true;

    while(1){
        if(!remelt) break;
        remelt = false;
        time++;
        int cnt = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]) {
                    Melt(i, j); 
                    cnt++;
                    final_melt = cnt;
                }
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(visited[i][j]) grid[i][j] = 0;
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]) remelt = true;
            }
        }

    }
    cout << time << " " << final_melt;
    return 0;
}