#include <iostream>

#define MAX_N 200
using namespace std;

int n, r, c;
int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

void Gravity(){
    
    for(int col=0; col<n; col++){
        int idx = n-1;
        for(int row=n-1; row>=0; row--){
            if(grid[row][col]!=0) temp[idx--][col] = grid[row][col];
        }
    }
}   

void Bomb(int r, int c){
    int power = grid[r][c];
    grid[r][c] = 0; // 중심점 폭발
    for(int i=1; i<power; i++){
        // 범위 체크 추가
        if(r-i >= 0) grid[r-i][c] = 0;
        if(r+i < n) grid[r+i][c] = 0;
        if(c-i >= 0) grid[r][c-i] = 0;
        if(c+i < n) grid[r][c+i] = 0;
    }
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
    cin >> r >> c;
    Bomb(r-1, c-1);
    Gravity();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << temp[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}