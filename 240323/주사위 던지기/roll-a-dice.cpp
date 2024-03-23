#include <iostream>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;
int n, m, r, c;
int cur_r, cur_c;
int grid[MAX_N][MAX_N];
int up, front, rightt;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Dir(char dir){
    if(dir == 'U'){
        return 0;
    }
    else if(dir == 'R'){

        return 1;
    }
    else if(dir == 'D'){
        return 2;
    }
    else if(dir == 'L'){
        return 3;
    }
}

void Roll(int x, int y, int dir){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    int new_x = x + dx[dir];
    int new_y = y + dy[dir];
    int temp;
    if(InRange(new_x, new_y)){
        if(dir == 0){
            temp = front;
            front = 7 - up;
            up = temp;
        }
        else if(dir == 1){
            temp = rightt;
            rightt = up;
            up = 7 - temp;
        }
        else if(dir == 2){
            temp = front;
            front = up;
            up = 7 - temp;
        }
        else if(dir == 3){
            temp = up;
            up = rightt;
            rightt = 7 - temp;
        }
        grid[new_x][new_y] = 7 - up;
        cur_r = x + dx[dir];
        cur_c = y + dy[dir];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> r >> c;
    up = 1, front = 2, rightt = 3;
    cur_r = r-1, cur_c = c-1;
    grid[cur_r][cur_c] = 6;
    while(m--){
        char dir;
        cin >> dir;
        Roll(cur_r, cur_c, Dir(dir));
    }
    int sum = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] != 0) sum += grid[i][j];
        }
    }
    cout << sum;
    return 0;
}