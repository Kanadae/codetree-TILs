#include <iostream>
#include <algorithm>
#define MAX_N 20
using namespace std;

int N, ans;
int grid[MAX_N][MAX_N];

int GetGold(int row_s, int col_s, int row_e, int col_e){
    int gold = 0;
    for(int i=row_s; i<=row_e; i++){
        for(int j=col_s; j<=col_e; j++){
            if(grid[i][j]) gold++;
        }
    }
    return gold;
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
    for(int i=0; i<N-2; i++){
        for(int j=0; j<N-2; j++){
            int gold = GetGold(i, j, i+2, j+2);
            ans = max(ans, gold);
        }
    }
    cout << ans;
    return 0;
}