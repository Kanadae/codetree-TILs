#include <iostream>
#include <algorithm>

#define MAX 51
#define DIR_NUM 4

using namespace std;

int N, M;
int grid[MAX][MAX];
bool visited[MAX][MAX];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < M;
}

void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            visited[i][j] = false;
        }
    }
}

void DFS(int x, int y, int h){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    visited[x][y] = true;
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] - h > 0){
            DFS(new_x, new_y, h);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int maxHeight = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> grid[i][j];
            maxHeight = max(maxHeight, grid[i][j]);
        }
    }
    int maxCnt = 0;
    int minH = 101;
    for(int h=1; h<maxHeight; h++){
        int cnt = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(visited[i][j] || grid[i][j] - h <= 0) continue;
                DFS(i, j, h);
                cnt++;
            }
        }
        init();
        if(maxCnt < cnt) minH = h;
        maxCnt = max(maxCnt, cnt);
        
    }
    if(maxCnt == 0) cout << "1" << " " << maxCnt; 
    else cout << minH << " " << maxCnt; 
    return 0;
}