#include <iostream>
#include <queue>
#include <tuple>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n, k;
int target;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
queue<pair<int, int>> q;
pair<int, int> cur_num;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool NeedUpdate(pair<int, int> best_pos, pair<int, int> new_pos) {
    if(best_pos == make_pair(-1, -1))
        return true;
    
    int best_x, best_y;
    tie(best_x, best_y) = best_pos;
    
    int new_x, new_y;
    tie(new_x, new_y) = new_pos;
    
    return make_tuple(grid[new_x][new_y], -new_x, -new_y) >
           make_tuple(grid[best_x][best_y], -best_x, -best_y);
}

void BFS(){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    int cur_x, cur_y;
    tie(cur_x, cur_y) = cur_num;
    visited[cur_x][cur_y] = true;
    q.push(cur_num);
    target = grid[cur_x][cur_y];
    
    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] < target){
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

bool Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }

    BFS();
    pair<int, int> ans_pos = make_pair(-1, -1);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!visited[i][j] || cur_num == make_pair(i, j)) continue;

            pair<int, int> new_pos = make_pair(i, j);
            if(NeedUpdate(ans_pos, new_pos))
                ans_pos = new_pos;
        }
    }

    if(ans_pos == make_pair(-1, -1)) return false;
    else {
        cur_num = ans_pos;
        return true;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    int r, c;
    cin >> r >> c;
    cur_num = make_pair(r-1, c-1);
    while(k--){
        if(!Simulate()) break;
    }

    int ans_x, ans_y;
    tie(ans_x, ans_y) = cur_num;
    cout << ans_x+1 << " " << ans_y+1;
    return 0;
}