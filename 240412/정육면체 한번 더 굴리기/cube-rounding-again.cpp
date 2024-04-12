#include <iostream>
#include <tuple>
#include <queue>

#define MAX_N 20
#define DIR_NUM 4
using namespace std;

int n, m;
int grid[MAX_N][MAX_N];
int up = 1, front = 2, ryght = 3;
int dir = 1;
pair<int, int> dice;
int ans;
bool visited[MAX_N][MAX_N];
queue<pair<int, int>> q;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }
}

void BFS(int target) {
    int dx[DIR_NUM] = { -1, 0, 1, 0 }, dy[DIR_NUM] = { 0, 1, 0, -1 };

    while (!q.empty()) {
        pair<int, int> cur_pos = q.front();
        int x = cur_pos.first;
        int y = cur_pos.second;
        q.pop();
        for (int i = 0; i < DIR_NUM; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (InRange(new_x, new_y) && !visited[new_x][new_y] && grid[new_x][new_y] == target) {
                ans += target;
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

void Simulate() {
    int dx[DIR_NUM] = { -1, 0, 1, 0 }, dy[DIR_NUM] = { 0, 1, 0, -1 };
    int x, y;
    tie(x, y) = dice;

    int new_x = x + dx[dir];
    int new_y = y + dy[dir];
    if (!InRange(new_x, new_y)) {
        dir = (dir + 2) % 4;
        new_x = x + dx[dir];
        new_y = y + dy[dir];
    }

    if (dir == 0) {
        int temp = up;
        up = front;
        front = 7 - temp;
    }
    else if (dir == 1) {
        int temp = ryght;
        ryght = up;
        up = 7 - temp;
    }
    else if (dir == 2) {
        int temp = front;
        front = up;
        up = 7 - temp;
    }
    else if (dir == 3) {
        int temp = up;
        up = ryght;
        ryght = 7 - temp;
    }

    // cout << up << " " << front << " " << ryght << "\n";

    dice = make_pair(new_x, new_y);
    Init();
    q.push(make_pair(new_x, new_y));
    visited[new_x][new_y] = true;
    ans += grid[new_x][new_y];
    BFS(grid[new_x][new_y]);

    if (7 - up > grid[new_x][new_y]) {
        dir = (dir + 1) % 4;
    }
    else if (7 - up < grid[new_x][new_y]) {
        dir = (dir + 3) % 4;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    while (m--) {
        Simulate();
        // cout << ans << "\n";
    }
    cout << ans;
    return 0;
}