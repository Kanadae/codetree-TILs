#include <iostream>

#define MAX_N 101
#define BLANK -1
using namespace std;

int n, m, k;
int end_of_column;
int bomb1[MAX_N];
int bomb2[MAX_N][MAX_N];
int copy_bomb2[MAX_N][MAX_N];
int temp[MAX_N];

int GetEndOfExplosion(int start_idx, int cur_num){
    int end_idx = start_idx + 1;

    while(end_idx < end_of_column){
        if(bomb1[end_idx] == cur_num)
            end_idx++;
        else break;
    }
    return end_idx - 1;
}

void FillZero(int start_idx, int end_idx){
    for(int i=start_idx; i<=end_idx; i++){
        bomb1[i] = 0;
    }
}

void MoveToTemp(){
    int temp_idx = 0;
    for(int i=0; i<end_of_column; i++){
        if(bomb1[i] != 0){
            temp[temp_idx++] = bomb1[i];
        }
    }

    end_of_column = temp_idx;
    for(int i=0; i<end_of_column; i++){
        bomb1[i] = temp[i];
    }
}

// bomb1의 폭탄에서 m이상 연속인 부분은 터트림
void Explode(){
    bool did_explode = false;

    for(int cur_idx = 0; cur_idx<end_of_column; cur_idx++){
        if(bomb1[cur_idx] == 0) continue;

        int end_idx = GetEndOfExplosion(cur_idx, bomb1[cur_idx]);

        if(end_idx - cur_idx + 1 >= m) {
            did_explode = true;
            FillZero(cur_idx, end_idx);
        }
    }
    MoveToTemp();
}

// rotate 이후에 중력으로 가라앉히고 그 열의 폭탄을 bomb1에 담음
void CopyColumn(int col){
    end_of_column = 0;
    for(int i=0; i<n; i++){
        if(bomb2[i][col] != BLANK)
            bomb1[end_of_column++] = bomb2[i][col];
    }
}

// 밑바닥부터 폭탄을 다시 쌓음
void CopyResult(int col){
    int result_idx = end_of_column - 1;
    for(int i=n-1; i>=0; i--){
        if(result_idx >= 0) bomb2[i][col] = bomb1[result_idx--];
    }
}

//그냥 단순히 회전하는 부분
void Rotate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_bomb2[i][j] = BLANK;
        }
    }

    for(int j=0; j<n; j++){
        int copy_idx = n-1;
        for(int i=n-1; i>=0; i--){
            copy_bomb2[j][n-i-1] = bomb2[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            bomb2[i][j] = copy_bomb2[i][j];
        }
    }
}

void Simulate(){
    for(int col=0; col<n; col++){
        CopyColumn(col);
        Explode();
        CopyResult(col);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> bomb2[i][j];
        }
    }

    Simulate();
    /*
    cout << "After Simulate\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << bomb2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    */
    while(k--){
        Rotate();
        /*
        cout << "After Rotate\n";
        for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << bomb2[i][j] << " ";
        }
        cout << "\n";
        
    }
    cout << "\n";
    */
        Simulate();
        /*
        cout << "After Simulate\n";
        for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << bomb2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    */
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           if(bomb2[i][j] != BLANK) ans++;
        }
    }
    cout << ans;
    return 0;
}