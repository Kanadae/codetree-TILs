#include <iostream>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;

int N, M, K;
int total_time;
int cur_x, cur_y;
int grid[MAX_N][MAX_N];
int tail[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else return 3;
}

void Move(int dir, int dist){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    int new_x = cur_x + dx[dir];
    int new_y = cur_y + dy[dir];

    while(dist--){
        total_time++;
        if(InRange(new_x, new_y) && !grid[new_x][new_y]){
            if(grid[new_x][new_y] == 2){
                grid[new_x][new_y] = 1;
                cur_x = new_x, cur_y = new_y;
            }
            else{
                grid[new_x][new_y] = 1;
                tail[cur_x][cur_y] = 0;
                tail[new_x][new_y] = 1;
                cur_x = new_x, cur_y = new_y;
            }
        }
        else return;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    grid[cur_x][cur_y] = 1;
    tail[cur_x][cur_y] = 1;
    for(int i=0; i<M; i++){
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1] = 2;
    }

    while(K--){
        char dir;
        int dist;
        cin >> dir >> dist;
        Move(Dir(dir), dist);
    }
    cout << total_time;
    return 0;
}