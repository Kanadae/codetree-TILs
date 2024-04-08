#include <iostream>
#include <queue>
using namespace std;

int map[21][21];
int n,m,d;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0}; // 우하좌상
bool visited[21][21];
int cur_num;
int sum;
int x,y;
int u = 1,f = 2,r = 3, floor = 6;
queue<pair<int,int>> q;

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move()
{
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (!inRange(nx,ny))
    {
        if (d < 2) d += 2;
        else d -= 2;
        nx = x + dx[d];
        ny = y + dy[d];
    }
    x = nx; y = ny;
    int uu, ff, rr;
    if (d == 0)
    {
        uu = 7 - r;
        ff = f;
        rr = u;   
    }
    if (d == 1)
    {
        uu = 7-f;
        ff = u;
        rr = r;
    }
    if (d == 2)
    {
        uu = r;
        ff = f;
        rr = 7 - u;
    }
    if (d == 3)
    {
        uu = f;
        ff = 7-u;
        rr = r;
    }
    u = uu;
    f = ff;
    r = rr;
    floor = 7 - u;
}

void bfs()
{
    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (inRange(nx,ny) && !visited[nx][ny] && cur_num == map[nx][ny])
            {
                visited[nx][ny] = true;
                sum += cur_num;
                q.push(make_pair(nx,ny));
            }
        }
    }
}

int getScore()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            visited[i][j] = false;
    sum = 0;
    cur_num = map[x][y];
    q.push(make_pair(x,y));
    visited[x][y] = true;
    sum += cur_num;
    bfs();
    if (floor > cur_num)
    {
        d = (d+1) % 4;
    } else if (floor < cur_num) d = (d+3) % 4;
    return sum;
}

int main() {
    cin >> n >> m;
    for (int i =0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];

    
    int ans = 0;
    while (m--)
    {
        Move();
        ans += getScore();
    }
    cout << ans;
    return 0;
}