#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;

int n, k, m;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int ans;
queue<pair<int, int>> q;
vector<pair<int, int>> start;
vector<pair<int, int>> stone;
vector<pair<int, int>> selected_stone;

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
            if(InRange(new_x, new_y) && !visited[new_x][new_y] && !grid[new_x][new_y]){
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

int Calc() {
	for(int i = 0; i < m; i++) {
		int x = selected_stone[i].first, y = selected_stone[i].second;
		grid[x][y] = 0;
	}
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			visited[i][j] = 0;
		
    // k개의 시작점을 queue에 넣고 시작합니다.
	// BFS는 여러 시작점에서 시작하여
    // 이동 가능한 칸을 전부 탐색하는 것이 가능합니다.
    for(int i = 0; i < k; i++) {
		q.push(start[i]);
		visited[start[i].first][start[i].second] = true;
	}

    BFS();
	
	for(int i = 0; i < m; i++) {
		int x = selected_stone[i].first, y = selected_stone[i].second;
		grid[x][y] = 1;
	}

    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(visited[i][j])
			    cnt++;
	return cnt;
}

void DFS(int cur_num, int cnt){
    if(cnt == m){
        ans = max(ans, Calc());
        return;
    }

    if(cur_num == stone.size()) return;

    selected_stone.push_back(stone[cur_num]);
	DFS(cur_num + 1, cnt + 1);
	selected_stone.pop_back();
	
	DFS(cur_num + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j]) stone.push_back(make_pair(i, j));
        }
    }
    int kk = k;
    while(kk--){
        int r, c;
        cin >> r >> c;
        start.push_back(make_pair(r-1, c-1));
    }
    DFS(0, 0);
    cout << ans;
    return 0;
}