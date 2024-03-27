#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

#define DIR_NUM 4
#define MAX_N 9
using namespace std;

int n, k, u, d;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int ans;
vector<pair<int, int>> pos;
vector<pair<int, int>> s_pos;
queue<pair<int, int>> q;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y]){
                if(abs(grid[new_x][new_y]-grid[x][y]) >= u && abs(grid[new_x][new_y]-grid[x][y]) <= d){
                    visited[new_x][new_y] = true;
                    q.push(make_pair(new_x, new_y));
                }
            }
        }
    }
}

int Calc(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }

    for(int i=0; i<k; i++){
        q.push(s_pos[i]);
        visited[s_pos[i].first][s_pos[i].second] = true;
    }

    BFS();

    int cnt = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]) cnt++;
        }
    }
    return cnt;
}

void FindMax(int cur_idx, int cnt){
    if(k == cnt){
        ans = max(ans, Calc());
        return;
    }

    if(cur_idx == n * n) return;

    s_pos.push_back(pos[cur_idx]);
    FindMax(cur_idx+1, cnt+1);
    s_pos.pop_back();

    FindMax(cur_idx+1, cnt);
} 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> u >> d;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            pos.push_back(make_pair(i, j));
        }
    }
    FindMax(0, 0);
    cout << ans;
    return 0;
}