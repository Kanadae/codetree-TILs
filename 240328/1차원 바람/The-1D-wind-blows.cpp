#include <iostream>

#define MAX 101
using namespace std;

int N, M, Q;
int grid[MAX][MAX];

bool InRange(int x){
    return 0 <= x && x < N;
}

int Dir(char dir){
    if(dir == 'L') return 0;
    else return 1;
}

void Shift(int row, int dir){
    int temp;

    if(dir == 0) {
        temp = grid[row][M-1];
        for(int i=M-1; i>0; i--){
            grid[row][i] = grid[row][i-1];
        }
        grid[row][0] = temp;
    }
    else {
        temp = grid[row][0];
        for(int i=0; i<M-1; i++){
            grid[row][i] = grid[row][i+1];
        }
        grid[row][M-1] = temp;
    }
}

bool Compare(int row1, int row2){
    for(int i=0; i<M; i++){
        if(grid[row1][i] == grid[row2][i]) return true;
    }
    return false;
}

void Simulate(int row, int dir){
    Shift(row, dir);
    int up_dir = !dir;
    int down_dir = !dir;

    int up_row = row;
    int down_row = row;

    while(InRange(up_row-1)){
        if(Compare(up_row, up_row-1)){
            Shift(up_row-1, up_dir);
            up_dir = !up_dir;
            up_row--;
        }
        else break;
    }

    while(InRange(down_row+1)){
        if(Compare(down_row, down_row+1)){
            Shift(down_row+1, down_dir);
            down_dir = !down_dir;
            down_row++;
        }
        else break;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> grid[i][j];
        }
    }
    int row;
    char dir;
    while(Q--){
        cin >> row >> dir;
        Simulate(row-1, Dir(dir));
        
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    } 
    return 0;
}