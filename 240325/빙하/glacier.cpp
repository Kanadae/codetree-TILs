#include <iostream>
#include <queue>
using namespace std;

queue<pair<int,int>> q;
int n, m, t;
int map[201][201];
int visited[201][201];
int heat;
int rest;
bool canGo(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= m) return false;
    if (visited[x][y]) return false;
    return true;
}

void bfs()
{
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (canGo(new_x,new_y))
            {
                if (map[new_x][new_y] == 1)
                {
                    visited[new_x][new_y] = true;
                    map[new_x][new_y] = 0;
                    heat++;
                } else {
                    visited[new_x][new_y] = true;
                    q.push(make_pair(new_x,new_y));
                }
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
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == 0 && !visited[i][j])
            {
                heat = 0;
                q.push(make_pair(i,j));
                bfs();
                if (heat != 0) rest = heat;
                
                if (heat == 0) break;
                t++;
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    visited[i][j]= false;
                }
            }
        }
    }
    cout << t << " " << rest;
    return 0;
}