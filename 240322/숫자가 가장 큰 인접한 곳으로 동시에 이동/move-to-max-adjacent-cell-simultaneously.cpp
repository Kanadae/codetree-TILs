#include <iostream>
#include <vector>

#define MAX_N 20
#define DIR_NUM 4
using namespace std;

int n, m, t;
int grid[MAX_N][MAX_N];
int count[MAX_N][MAX_N];
int next_count[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void init(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_count[i][j] = 0;
        }
    }
}

pair<int, int> GetMaxNeighborPos(int curr_x, int curr_y) {
    int dx[DIR_NUM] = {-1, 1, 0, 0}, dy[DIR_NUM] = {0, 0, -1, 1};

    int max_num = 0;
    pair<int, int> max_pos;
    
    for(int i = 0; i < DIR_NUM; i++) {
        int next_x = curr_x + dx[i];
        int next_y = curr_y + dy[i];
        
        if(InRange(next_x, next_y) && grid[next_x][next_y] > max_num) {
            max_num = grid[next_x][next_y];
            max_pos = make_pair(next_x, next_y);
        }
    }
    return max_pos;
}

void Move(int x, int y) {
    pair<int, int> next_pos = GetMaxNeighborPos(x, y);
    int next_x = next_pos.first, next_y = next_pos.second;
    
    next_count[next_x][next_y]++;
}


void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(count[i][j]) Move(i, j);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            count[i][j] = next_count[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(count[i][j] >= 2) count[i][j] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> t;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    for(int i=0; i<m; i++){
        int r, c;
        cin >> r >> c;
        count[r-1][c-1] = 1;
    }

    while(t--){
        init();
        Simulate();

    }

    int ans = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(count[i][j]) ans++;
        }
    }
    cout << ans;
    return 0;
}