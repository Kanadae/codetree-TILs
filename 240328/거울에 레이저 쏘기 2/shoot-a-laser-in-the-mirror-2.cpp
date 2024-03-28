#include <iostream>

#define MAX_N 1001
#define DIR_NUM 4
using namespace std;

int n, k;
char grid[MAX_N][MAX_N];
int x, y, dir;

void FindDir(int start){
    if(start / n == 0){
        dir = 0;
        x = 0;
        y = start % n;
    }
    else if(start / n == 1){
        dir = 1;
        x = (start-1) % n;
        y = n-1;
    }
    else if(start / n == 2){
        dir = 2;
        x = n-1;
        y = (n - (start % n)) % n;
    }
    else if(start / n == 3){
        dir = 3;
        x = (n - (start % n)) % n;
        y = 0;
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Move(int start){
    FindDir(start);
    int cnt = 1;
    int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, -1, 0, 1};

    if(grid[x][y] == '\\'){
        dir = 3 - dir;
    }
    else if(grid[x][y] == '/'){
        if(dir == 0) dir = 1;
        else if(dir == 1) dir = 0;
        else if(dir == 2) dir = 3;
        else if(dir == 3) dir = 2;
    }

    while(1){

        if(grid[x][y] == '\\'){
        dir = 3 - dir;
        }
        else if(grid[x][y] == '/'){
            if(dir == 0) dir = 1;
            else if(dir == 1) dir = 0;
            else if(dir == 2) dir = 3;
            else if(dir == 3) dir = 2;
        }
        x += dx[dir];
        y += dy[dir];
        cnt++;
        if(!InRange(x, y)) break;
    }
    return cnt;
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
    cin >> k;
    int ans = Move(k);
    cout << ans;
    return 0;
}