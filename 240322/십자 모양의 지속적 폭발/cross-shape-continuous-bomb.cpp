#include <iostream>

#define MAX_N 201
using namespace std;

int n, m;
int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

void Bomb(int col){
    int power;
    for(int i=0; i<n; i++){
        if(grid[i][col] != 0){
            power = grid[i][col];
            grid[i][col] = 0;
            for(int j=1; j<power; j++){
                if(i-j>=0) grid[i-j][col] = 0;
                if(i+j<n) grid[i+j][col] = 0;
                if(col-j>=0) grid[i][col-j] = 0;
                if(col+j<n) grid[i][col+j] = 0;
            }
            break;
        }
    }
}

void Gravity(){
    for(int col=0; col<n; col++){
        int idx = n-1;
        for(int row=n-1; row>=0; row--){
            if(grid[row][col] != 0) temp[idx--][col] = grid[row][col];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = temp[i][j];
            temp[i][j] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    while(m--){
        int col;
        cin >> col;
        Bomb(col-1);
        Gravity();
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}