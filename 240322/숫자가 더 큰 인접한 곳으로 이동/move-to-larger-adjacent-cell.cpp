#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n, r, c;
int grid[MAX_N][MAX_N];
bool CanGo;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y){
    cout << grid[x][y] << " ";
    int dx[DIR_NUM] = {-1, 1, 0, 0}, dy[DIR_NUM] = {0, 0, -1, 1};
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && grid[x][y] < grid[new_x][new_y]){
            x = new_x, y = new_y;
            Move(new_x, new_y);
            return;
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> r >> c;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    Move(r-1, c-1);
    return 0;
}