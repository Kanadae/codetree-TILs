#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int N, row, col, dir;
char grid[MAX_N][MAX_N];
int ans;
bool visited[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

bool Move(int x, int y, int cur_dir){
    int dx[DIR_NUM] = {0, 1, 0, -1}, dy[DIR_NUM] = {1, 0, -1, 0};
    visited[x][y] = true;
    int new_x = x + dx[cur_dir];
    int new_y = y + dy[cur_dir];

    if(grid[new_x][new_y] == '#') {
        dir = (dir + 3) % 4;
        return true;
    }
    ans++;
    if(!InRange(new_x, new_y)) return false;
    if(visited[new_x][new_y]){
        ans = -1;
        return false;
    }

    else if(grid[new_x][new_y] == '.'){
        if(dir == 0 && grid[new_x+1][new_y] != '#') dir = (dir + 1) % 4;
        else if(dir == 1 && grid[new_x][new_y-1] != '#') dir = (dir + 1) % 4;
        else if(dir == 2 && grid[new_x-1][new_y-1] != '#') dir = (dir + 1) % 4;
        else if(dir == 3 && grid[new_x][new_y+1] != '#') dir = (dir + 1) % 4;
        row = new_x + 1, col = new_y + 1;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> row >> col;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
        }
    }
    while(1){
        if(!Move(row-1, col-1, dir)) break;
    }
    cout << ans;
    return 0;
}