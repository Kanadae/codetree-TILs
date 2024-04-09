#include <iostream>
using namespace std;
int n,m,h,k;
int tree[100][100];
int runner[100][100][5]; // 도망자 좌표, 방향, 사람수.
int rdx[4] = {0,1,0,-1}; // 2 더하고 2 빼면 반대방향
int rdy[4] = {1,0,-1,0};

int dx[4] = {-1,0,1,0}; // + 1 % 4 시계방향, 상우하좌
int dy[4] = {0,1,0,-1}; // + 3 % 4 반시계 방향
int sx, sy; // 술래 위치
int sd; // 술래 얼굴 방향
int foot; // 술래 발자국 수
int clock_d = 1; // 1이면 시계방향, 3이면 반시계 방향
int new_runner[100][100][5];
int t = 1;
bool visited[100][100];

bool inRange(int x,int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void moveRunner()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int d = 0; d < 4; d++)
                new_runner[i][j][d] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int d = 0; d < 4; d++)
            {
                if (!runner[i][j][d]) continue;
                int dist = abs(sx - i) + abs(sy - j);
                if (dist > 3)
                {
                    new_runner[i][j][d] += runner[i][j][d];
                    continue;
                }
                int nx = i + rdx[d];
                int ny = j + rdy[d];
                int td = d;
                if (!inRange(nx,ny))
                {
                    if (d < 2) td = d + 2;
                    else td = d - 2;
                    nx = i + rdx[td];
                    ny = j + rdy[td];
                }
                if (nx == sx && ny == sy)
                {
                    nx = i; ny = j;
                }
                new_runner[nx][ny][td] += runner[i][j][d];
            }
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int d = 0; d < 4; d++)
                runner[i][j][d] = new_runner[i][j][d];

}

void init()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
}

void Print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}

int moveCatch()
{
    int score = 0;
    // 방향따라 한 칸 이동 후 방향 변경
    int x = sx + dx[sd];
    int y = sy + dy[sd];
    if (x == 0 && y == 0) // 0,0이면
    {
        clock_d = 3;
        init();
        sd = 2; // 아래로
    } else if (x == n/2 && y == n/2) // 중앙이면
    {
        clock_d = 1;
        init();
        sd = 0; // 위로
    }
    else if (clock_d == 1) // 시계 방향이라면
    {
        // 방향 회전해서 가보기
        int td = (sd + clock_d) % 4;
        int tx = x + dx[td];
        int ty = y + dy[td];
        if (!visited[tx][ty]) sd = td;
    } else if (clock_d == 3)
    {
        // 가던 방향으로 가보기
        int tx = x + dx[sd];
        int ty = y + dy[sd];
        if (!inRange(tx,ty) || visited[tx][ty])
        {
            sd = (sd + 3) % 4; // 반시계로 회전
        }
    }
    visited[x][y] = true;
    sx = x; sy = y;
    for (int i = 0; i < 3; i++)
    {
        int nx = x + i * dx[sd];
        int ny = y + i * dy[sd];
        if (!inRange(nx,ny)) break;
        if (tree[nx][ny] == 1) continue;
        for (int j = 0; j < 4; j++)
        {
            if (runner[nx][ny][j])
            {
                score += runner[nx][ny][j];
                runner[nx][ny][j] = 0;
            }
        }
    }


    return score;
}

int main() {
    cin >> n >> m >> h >> k;
    sx = n / 2; sy = n / 2;
    visited[sx][sy] = true;
    for (int i = 0; i < m; i++)
    {
        int x,y,d;
        cin >> x >> y >> d;
        x--; y--; d--;
        runner[x][y][d]++;
    }
    for (int i = 0; i < h; i++)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        tree[x][y] = 1;
    }

    int ans = 0;
    for (t = 1; t <= k; t++)
    {
        // 도망자 이동
        moveRunner();
        // 술래 이동
        ans += moveCatch() * t;
    }

    cout << ans;

    return 0;
}