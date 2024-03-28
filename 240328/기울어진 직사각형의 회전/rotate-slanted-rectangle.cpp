#include <iostream>

#define MAX_N 100
using namespace std;
int n;
int grid[MAX_N][MAX_N];
int arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    int r, c, m1, m2, m3, m4, dir;
    cin >> r >> c >> m1 >> m2 >> m3 >> m4 >> dir;

    int idx = 1;
    arr[0] = grid[r-1][c-1];

    int cur_row = r, cur_col = c;

    for(int i=1; i<=m1; i++){
        arr[idx++] = grid[cur_row-i-1][cur_col+i-1];
        r--; c++;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m2; i++){
        arr[idx++] = grid[cur_row-i-1][cur_col-i-1];
        r--; c--;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m3; i++){
        arr[idx++] = grid[cur_row+i-1][cur_col-i-1];
        r++; c--;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m4-1; i++){
        arr[idx++] = grid[cur_row+i-1][cur_col+i-1];
        r++; c++;
    }
    r++; c++;
    cur_row = r, cur_col = c;
    
    if(dir==1){
        int temp = arr[0];
        for(int i=0; i<idx-1; i++){
            arr[i] = arr[i+1];
        }
        arr[idx-1] = temp;
    }
    else{
        int temp = arr[idx-1];
        for(int i=idx-1; i>0; i--){
            arr[i] = arr[i-1];
        }
        arr[0] = temp;
    }

    grid[r-1][c-1] = arr[0];
    int j = 1;

    for(int i=1; i<=m1; i++){
        grid[cur_row-i-1][cur_col+i-1] = arr[j++];
        r--; c++;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m2; i++){
        grid[cur_row-i-1][cur_col-i-1] = arr[j++];
        r--; c--;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m3; i++){
        grid[cur_row+i-1][cur_col-i-1] = arr[j++];
        r++; c--;
    }
    cur_row = r, cur_col = c;
    for(int i=1; i<=m4-1; i++){
        grid[cur_row+i-1][cur_col+i-1] = arr[j++];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}