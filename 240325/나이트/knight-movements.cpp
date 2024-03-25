#include <iostream>
#include <queue>

#define DIR_NUM 8
#define MAX_N 101
using namespace std;

int n;
int r1, r2, c1, c2;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];

queue<pair<int, int>> q;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void bfs(){
    int dx[DIR_NUM] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[DIR_NUM] = {-1, 1, -2, 2, -2, 2, 1, -1};

    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y]){
                visited[new_x][new_y] = true;
                step[new_x][new_y] = step[x][y] + 1;
                if(new_x == r2-1 && new_y == c2-1) return;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> r1 >> c1 >> r2 >> c2;
    visited[r1-1][c1-1] = true;
    q.push(make_pair(r1-1, c1-1));
    step[r2-1][c2-1] = -1;
    bfs();
    if(r1==r2 && c1==c2) cout << "0";
    else cout << step[r2-1][c2-1];
    return 0;
}