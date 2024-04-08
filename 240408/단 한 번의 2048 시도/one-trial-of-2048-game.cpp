#include <iostream>

using namespace std;

int n = 4;
int grid[4][4];
int copy_grid[4][4];

int Dir(char dir){
    if(dir == 'D') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'U') return 2;
    else return 3;
}

void Drop(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_grid[i][j] = 0;
        }
    }

    for(int j=0; j<n; j++){
        int keep_num = -1;
        int cur_idx = n-1;

        for(int i=n-1; i>=0; i--){
            if(!grid[i][j]) continue;
            
            if(keep_num == -1) {
                keep_num = grid[i][j];
            }
            else if(grid[i][j] == keep_num){
                copy_grid[cur_idx--][j] = keep_num * 2;
                keep_num = -1;
            }
            else{
                copy_grid[cur_idx--][j] = keep_num;
                keep_num = grid[i][j];
            }
        }

        if(keep_num != -1) copy_grid[cur_idx][j] = keep_num;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = copy_grid[i][j];
        }
    }
}

void Rotate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_grid[i][j] = 0;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_grid[j][n-i-1] = grid[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = copy_grid[i][j];
        }
    }
}

void Simulate(int dir){
    for(int i=0; i<dir; i++)
        Rotate();

    Drop();

    for(int i=0; i<4-dir; i++)
        Rotate();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    char dir;
    cin >> dir;
    Simulate(Dir(dir));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}