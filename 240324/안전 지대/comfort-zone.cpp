#include <iostream>
using namespace std;
int n,m;
int map[51][51];
bool visited[51][51];
int k = 1;
int static_k;
int max_k;
int area;
int max_area;

bool Cango(int x,int y)
{
    if (0 > x || x >= n || 0 > y || y >= m) return false;
    if (visited[x][y]) return false;
    return true;
}

void dfs(int x, int y)
{
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (Cango(new_x,new_y))
        {
            visited[new_x][new_y] = true;
            dfs(new_x, new_y);
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
            if (max_k < map[i][j]) max_k = map[i][j];
        }
    }
    static_k = max_k;
    max_k = 0;
    k = 1;
    while (k <= static_k)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (map[i][j] <= k)
                {
                    visited[i][j] = true;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j]) continue;
                dfs(i,j);
                area++;
            }
        }

        if (max_area < area)
        {
            max_area = area;
            max_k = k;
        }
        area = 0;
        k++;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                visited[i][j] = false;           }
        }
    }

    cout << max_k << " " << max_area;

    return 0;
}