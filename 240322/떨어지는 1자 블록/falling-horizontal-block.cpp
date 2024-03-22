#include <iostream>

#define MAX_N 100
using namespace std;

int n, m, k;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Fall(int m, int col){
    for(int i=0; i<n; i++){
        for(int j=col; j<col+m; j++){
            if(grid[i][j] == 1){
                for(int k=col; k<col+m; k++){
                    grid[i-1][k] = 1;
                }
                return;
            }
            else if(!InRange(i+1, j)){
                for(int k=col; k<col+m; k++){
                    grid[i][k] = 1;
                }
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    Fall(m, k-1);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}