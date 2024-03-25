#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

queue<pair<int, int>> q;
int n, k;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] == 1){
                temp[new_x][new_y] = temp[x][y] + 1;
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

void init(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            temp[i][j] = 0;
        }
    }
}

void init2(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            step[i][j] = 10001;
        }
    }
}

void FindMinTime(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]){
                step[i][j] = min(step[i][j], temp[i][j]);
            }
            else step[i][j] = -1;
        }
    }
}

void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 2){
                q.push(make_pair(i, j));
                visited[i][j] = true;
                init2();
                temp[i][j] = 0;
                BFS();
                FindMinTime();
                init();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    Simulate();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] != 2 && step[i][j] == 10001)
                cout << "-2 ";
            else
                cout << step[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}