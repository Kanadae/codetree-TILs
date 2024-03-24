#include <iostream>
#include <vector>
using namespace std;

int n,m;
int visited[101][101];
int map[101][101];
int ans;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= m) return false;
    if (!map[x][y]) return false;
    if (visited[x][y]) return false;
    return true;
}

void dfs(int x, int y)
{
    int dx[2] = {0, 1};
    int dy[2] = {1, 0};
    visited[x][y] = 1;
    for (int i = 0; i < 2; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (Cango(new_x,new_y))
        {
            dfs(new_x,new_y);
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

    dfs(0,0);
    if (visited[n-1][m-1]) cout << 1; else cout << 0;
    return 0;
}