#include <iostream>

#define DIR_NUM 4
#define MAX_N 100
using namespace std;

int N, T;
int ans;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >>  N >> T;
    string op;
    cin >> op;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
        }
    }
    int x = N/2, y = N/2, dir = 0;
    ans += grid[x][y];
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    for(int i=0; i<T; i++){
        if(op[i] == 'L'){
            dir = (dir + 3) % 4;
        }
        else if(op[i] == 'R'){
            dir = (dir + 1) % 4;
        }
        else if(op[i] == 'F'){
            int new_x = x + dx[dir];
            int new_y = y + dy[dir];
            if(InRange(new_x, new_y)){
                ans += grid[new_x][new_y];
                x = new_x, y = new_y;
            }
        }
    }
    cout << ans;
    return 0;
}