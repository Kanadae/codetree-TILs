#include <iostream>

#define MAX 101
using namespace std;

int N, M, Q;
int grid[MAX][MAX];
bool visited[MAX];

bool InRange(int x){
    return 0 <= x && x < N;
}

int Dir(char dir){
    if(dir == 'L') return 0;
    else return 1;
}

void Simulate(int row, int dir){
    int temp;
    visited[row] = true;
    if(dir == 0) {
        temp = grid[row][M-1];
        for(int i=M-1; i>0; i--){
            grid[row][i] = grid[row][i-1];
        }
        grid[row][0] = temp;
    }
    else {
        temp = grid[row][0];
        for(int i=0; i<M; i++){
            grid[row][i] = grid[row][i+1];
        }
        grid[row][M-1] = temp;
    }

    for(int i=0; i<M; i++){
        if(InRange(row-1) && !visited[row-1] && grid[row][i] == grid[row-1][i]){
            Simulate(row-1, !dir);
        }
        else if(InRange(row+1) && !visited[row+1] && grid[row][i] == grid[row+1][i]){
            Simulate(row+1, !dir);
        }
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
        for(int i=0; i<N; i++) visited[i] = false;
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