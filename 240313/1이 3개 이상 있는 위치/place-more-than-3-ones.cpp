#include <iostream>

#define MAX_N 101
#define DIR_NUM 4

int N;
int grid[MAX_N][MAX_N];
using namespace std;

int ans;

void Simulate(int x, int y){
    int one_num = 0;
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(grid[new_x][new_y] == 1) one_num++;
    }
    if(one_num >= 3) ans++;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            Simulate(i, j);
        }
    }
    cout << ans;
    return 0;
}