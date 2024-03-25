#include <iostream>
#include <queue>
#define MAX_N 100
using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

queue<pair<int, int>> q;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(){
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        q.pop();

        int x = cur_pos.first;
        int y = cur_pos.second;
        for(int i=0; i<4; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y]){
                visited[new_x][new_y] = true;
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
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    q.push(make_pair(0, 0));
    BFS();
    if(visited[n-1][m-1]) cout << "1";
    else cout << "0";
    return 0;
}