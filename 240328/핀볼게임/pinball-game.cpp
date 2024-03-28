#include <iostream>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;

int n, ans;
int grid[MAX_N][MAX_N];
int x, y, dir;

void FindDir(int start){
    if(start / n == 0){
        dir = 0;
        x = 0;
        y = start % n;
    }
    else if(start / n == 1){
        dir = 1;
        x = start % n;
        y = n-1;
    }
    else if(start / n == 2){
        dir = 2;
        x = n-1;
        y = start % n;
    }
    else{
        dir = 3;
        x = start % n;
        y = 0;
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Move(int start){
    int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, -1, 0, 1};
    // 남 서 북 동
    FindDir(start);
    int time = 1;

    while(1){
        if(grid[x][y] == 1) {
            if(dir == 0) dir = 1;
            else if(dir == 1) dir = 0;
            else if(dir == 2) dir = 3;
            else if(dir == 3) dir = 2;
        }
        else if(grid[x][y] == 2) {
            if(dir == 0) dir = 3;
            else if(dir == 1) dir = 2;
            else if(dir == 2) dir = 1;
            else if(dir == 3) dir = 0;
        }
        
        int new_x = x + dx[dir];
        int new_y = y + dy[dir];
        time++;
        if(InRange(new_x, new_y)) x = new_x, y = new_y;
        
        else break;
    }
    return time;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    int turn = 4 * n;
    for(int i=0; i<turn; i++){
        int cnt = Move(i);
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}