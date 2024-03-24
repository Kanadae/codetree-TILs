#include <iostream>
using namespace std;
int n;
int map[101][101];
int visited[101][101];
int max_block;
int block;
int pop_block;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    return true;
}

void dfs(int x, int y, int num)
{
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (Cango(new_x,new_y) && map[new_x][new_y] == num)
        {
            block++;
            visited[new_x][new_y] = true;
            dfs(new_x,new_y,num);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited[i][j]) continue;
            block++;
            visited[i][j] = true;
            dfs(i,j,map[i][j]);
            if (block >= 4) pop_block++;
            if (max_block < block) max_block = block;
            block = 0;               
        }
    }

    cout << pop_block << " " << max_block;
    return 0;
}