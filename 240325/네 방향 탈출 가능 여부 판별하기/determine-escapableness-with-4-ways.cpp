#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, m;
int map[101][101];
bool visited[101][101];
queue<pair<int,int>> q;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= m) return false;
    if (visited[x][y]) return false;
    if (!map[x][y]) return false;
    return true;
}

void bfs()
{
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (Cango(new_x,new_y))
            {
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x,new_y));
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
    q.push(make_pair(0,0));
    bfs();
    if (visited[n-1][m-1]) cout << 1; else cout << 0;
    return 0;
}