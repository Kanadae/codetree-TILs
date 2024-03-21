#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    int x = n / 2, y = n / 2;
    int dir = 0, move = 1, num = 1;
    grid[x][y] = num++;
    int dx[DIR_NUM] = {0, -1, 0, 1}, dy[DIR_NUM] = {1, 0, -1, 0};

    while(InRange(x, y)){
        for(int i=0; i<move; i++){
            x = x + dx[dir];
            y = y + dy[dir];
            grid[x][y] = num++;
        }

        dir = (dir + 1) % 4;
        if(dir == 0 || dir == 2) move++;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}