#include <iostream>

#define MAX_N 101
#define DIR_NUM 4

using namespace std;
int N, M;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;

    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=0; i<M; i++){
        int r, c;
        cin >> r >> c;
        grid[r-1][c-1] = 1;
        int cnt = 0;
        for(int dir=0; dir<DIR_NUM; dir++){
            int new_r = r-1 + dx[dir];
            int new_c = c-1 + dy[dir];
            if(InRange(new_r, new_c) && grid[new_r][new_c] == 1) cnt++;
        }
        if(cnt == 3) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}