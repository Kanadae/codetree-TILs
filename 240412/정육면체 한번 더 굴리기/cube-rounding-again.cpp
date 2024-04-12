#include <iostream>
#include <queue>
using namespace std;
int n, m;
int map[21][21];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0}; // 우,하,좌,상
int u = 1, f = 2, r = 3;
int dir = 0; // 현재 방향
int curx = 0, cury = 0; // 현재 위치
int d; // 아랫면
bool visited[21][21];
queue<pair<int,int>> q;
int temp = 0;
int ans = 0;

bool inRange(int x,int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void bfs()
{
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inRange(nx,ny) || visited[nx][ny]) continue;
            if (map[nx][ny] == map[curx][cury])
            {
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
                temp++;
            }
        }
    }
}

void simulate()
{
    // 방향대로 한칸 이동
    curx = curx + dx[dir];
    cury = cury + dy[dir];
    // 주사위 굴리기
    if (dir == 0) // 우
    {
        u = 7-r;
        f = f;
        r = u;
    } else if (dir == 1)
    {
        u = 7 - f;
        f = u;
        r = r;
    } else if (dir == 2)
    {
        u = r;
        f = f;
        r = 7 - u;
    } else if (dir == 3)
    {
        u = f;
        f = 7-u;
        r = r;
    }

    d = 7 - u;

    visited[curx][cury] = true;
    temp = 1;
    q.push(make_pair(curx,cury));
    bfs();
    ans += temp * map[curx][cury];
    if (d > map[curx][cury])
    {
        dir = (dir + 1) % 4;
    } else if (d < map[curx][cury])
    {
        dir = (dir + 3) % 4;
    }
    int nx = curx + dx[dir];
    int ny = cury + dy[dir];
    if (!inRange(nx,ny))
    {
        if (dir < 2) dir += 2;
        else dir -= 2;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
    
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        simulate();
    }

    cout << ans;
    return 0;
}