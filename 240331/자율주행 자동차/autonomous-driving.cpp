#include <iostream>
#include <queue>
using namespace std;
int n,m;
int x,y,d;
int map[51][51];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
bool visited[51][51];


int sig = 1;

int main() {
    cin >> n >> m >> x >> y >> d;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    visited[x][y] = true;
    while (sig)
    {
        int forward = 0;
        int td = d;
        for (int i = 0; i < 4; i++)
        {
            td = (td + 3) % 4;  
            int nx = x + dx[td];
            int ny = y + dy[td];
            if (0 > nx || nx >= n || 0 > ny || ny >= m) continue;
            if (map[nx][ny] == 1) continue;
            if (visited[nx][ny]) continue;
            else
            {
                d = td;
                x = nx;
                y = ny;
                forward = 1;
                visited[x][y] = true;
                break;
            }
        }

        if (forward == 0)
        {
            int td = (d + 2) % 4;
            int tx = x + dx[td]; int ty = y + dy[td];
            if (0 > tx || tx >= n || 0 > ty || ty >= m || map[tx][ty] == 1)
            {
                sig = 0; break;
            }
            else 
            {
                x = tx; y = ty;
                visited[x][y] = true;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j]) ans++;
        }
    }

    cout << ans;

    return 0;
}