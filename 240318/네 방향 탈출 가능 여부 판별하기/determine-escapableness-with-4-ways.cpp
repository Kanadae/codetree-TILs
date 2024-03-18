#include <iostream>
#include <queue>
#include <deque>

using namespace std;

int map[101][101];
queue<pair<int, int>> q;
bool visited[101][101];
int n, m;
void Push(int x, int y)
{
    visited[x][y] = true;
    q.push(make_pair(x,y));   
}

bool Cango(int x, int y)
{
    if (!(0 <= x && x < n && 0 <= y && y < m)) return false;
    if (visited[x][y] || map[x][y] == 0) return false;
    return true;
}

void BFS()
{
    int dx[2] = {0, 1};
    int dy[2] = {1, 0};

    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();

        int x = cur.first;
        int y = cur.second;
        for (int i = 0; i < 2; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (Cango(new_x,new_y))
            {
                Push(new_x, new_y);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }
    Push(0,0);
    BFS();
    if (map[n-1][m-1]) cout << "1"; else cout << "0";
    return 0;
}