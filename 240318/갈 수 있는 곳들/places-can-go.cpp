#include <iostream>
#include <queue>
using namespace std;
int n, k;
int map[101][101];
bool visited[101][101];
int visit = 0;
queue<pair<int, int>> q;

void Push(int x, int y)
{
    visited[x][y] = true;
    visit++;
    q.push(make_pair(x,y));
}

bool canGo(int x, int y)
{
    if (!(0 <= x && x < n && 0 <= y && y < n)) return false;
    if (visited[x][y] || map[x][y]) return false;
    return true; 
}

void bfs()
{
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    while (!q.empty())
    {
        pair<int,int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (canGo(new_x,new_y)) Push(new_x,new_y);
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < k; i++)
    {
        int r, c;
        cin >> r >> c;
        r--; c--;
        if (canGo(r,c))
        Push(r,c);
        bfs();
    }
    cout << visit;
    return 0;
}