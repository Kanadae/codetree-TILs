#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>

#define DIR_NUM 4
#define MAX_N 101
using namespace std;

int n, k, ans = INT_MAX;
int r1, r2, c1, c2;
int grid[MAX_N][MAX_N];
pair<int, int> s_pos;
vector<pair<int, int>> break_wall;
vector<pair<int, int>> wall;
queue<pair<int, int>> q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
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
                step[new_x][new_y] = step[x][y] + 1;
            }
        }
    }
}

int Calc(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            step[i][j] = 0;
        }
    }

    for(int i=0; i<k; i++){
        grid[break_wall[i].first][break_wall[i].second] = 0;
    }
    q.push(s_pos);
    visited[s_pos.first][s_pos.second] = true;
    step[r2-1][c2-1] = INT_MAX;
    BFS();

    for(int i=0; i<k; i++){
        grid[break_wall[i].first][break_wall[i].second] = 1;
    }

    int dist = step[r2-1][c2-1];
    
    return dist;
}

void FindMin(int idx, int cnt){
    if(k == cnt){
        ans = min(ans, Calc());
        return;
    }

    if(idx == wall.size()) return;

    break_wall.push_back(wall[idx]);
    FindMin(idx+1, cnt+1);
    break_wall.pop_back();

    FindMin(idx+1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j]) wall.push_back(make_pair(i, j));
        }
    }
    cin >> r1 >> c1 >> r2 >> c2;
    s_pos = make_pair(r1-1, c1-1);
    FindMin(0, 0);
    if(ans == INT_MAX) cout << "-1";
    else cout << ans;
    return 0;
}