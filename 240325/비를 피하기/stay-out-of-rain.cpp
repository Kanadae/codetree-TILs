#include <iostream>
#include <queue>

#define DIR_NUM 4
#define MAX_N 100
using namespace std;

int n, h, m;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];
int ans[MAX_N][MAX_N];

queue<pair<int, int>> q;
pair<int, int> temp_pos = make_pair(-1, -1);

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        visited[x][y] = true;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] != 1){
                visited[new_x][new_y] = true;
                step[new_x][new_y] = step[x][y] + 1;
                if(grid[new_x][new_y] == 3) {
                    ans[temp_pos.first][temp_pos.second] = step[new_x][new_y];
                    return;
                }
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

void init(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            step[i][j] = false;
        }
    }
}

void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 2){
                q.push(make_pair(i, j));
                visited[i][j] = true;
                temp_pos.first = i, temp_pos.second = j;
                ans[i][j] = -1;
                BFS();
                init();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> h >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    Simulate();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}