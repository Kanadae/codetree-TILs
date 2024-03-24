#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 26
#define DIR_NUM 4
using namespace std;

int n;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
vector<int> arr;
int cnt;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void DFS(int x, int y){
    visited[x][y] = true;
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y]){
            cnt++;
            DFS(new_x, new_y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    int ans = 0, idx = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j] || !grid[i][j]) continue;
            visited[i][j] = true;
            cnt = 1;
            DFS(i, j);
            arr.push_back(cnt);
            ans++;
        }
    }
    cout << ans << "\n";
    sort(arr.begin(), arr.end());
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << "\n";
    }
    return 0;
}