#include <iostream>

#define MAX 101
#define DIR_NUM 4
using namespace std;

int N, M, Q;
int r1, c1, r2, c2;
int grid[MAX][MAX];
int next_grid[MAX][MAX];

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < M;
}

void Init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            next_grid[i][j] = 0;
        }
    }
}

void Wind(int r1, int c1, int r2, int c2){
    if (r1 >= r2 || c1 >= c2) return; // 직사각형의 크기 검증
    
    int temp = grid[r1][c2]; // 오른쪽 상단 모서리 값 저장

    // 상단 가로줄 오른쪽으로 이동
    for (int col = c2; col > c1; col--) {
        grid[r1][col] = grid[r1][col - 1];
    }

    // 오른쪽 세로줄 아래로 이동
    for (int row = r2; row > r1; row--) {
        grid[row][c2] = grid[row - 1][c2];
    }
    grid[r1 + 1][c2] = temp; // 저장된 오른쪽 상단 모서리 값 삽입

    int temp2 = grid[r2][c1]; // 왼쪽 하단 모서리 값 저장

    // 하단 가로줄 왼쪽으로 이동
    for (int col = c1; col < c2; col++) {
        grid[r2][col] = grid[r2][col + 1];
    }
    grid[r2][c2 - 1] = grid[r2 - 1][c2]; // 이전에 이동된 오른쪽 세로줄의 값 삽입

    // 왼쪽 세로줄 위로 이동
    for (int row = r1; row < r2; row++) {
        grid[row][c1] = grid[row + 1][c1];
    }
    grid[r2 - 1][c1] = temp2; // 저장된 왼쪽 하단 모서리 값 삽입
}

void Average(int r1, int c1, int r2, int c2){
    int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=r1; i<=r2; i++){
        for(int j=c1; j<=c2; j++){
            int sum = grid[i][j], cnt = 1;
    
            for(int dir=0; dir<DIR_NUM; dir++){
                int new_x = i + dx[dir];
                int new_y = j + dy[dir];
                if(InRange(new_x, new_y)){
                    sum += grid[new_x][new_y];
                    cnt++;
                }
            }
            int average = sum / cnt;
            next_grid[i][j] = average;
        }
    }

    for(int i=r1; i<=r2; i++){
        for(int j=c1; j<=c2; j++){
            grid[i][j] = next_grid[i][j];
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
    while(Q--){
        cin >> r1 >> c1 >> r2 >> c2;
        Init();
        Wind(r1-1, c1-1, r2-1, c2-1);
        Average(r1-1, c1-1, r2-1, c2-1);
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}