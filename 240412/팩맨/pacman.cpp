#include <iostream>

using namespace std;

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,-1,-1,-1,0,1,1,1};
int pdx[4] = {-1, 0, 1, 0};
int pdy[4] = {0, -1, 0, 1}; // 상 좌 하 우
int monster[26][4][4][8]; // t턴에 있는 몬스터의 x,y,d 수
int egg[26][4][4][8]; // 알
int dead[4][4]; // 시체의 남은 턴 수 t
bool visited[4][4];

int n = 4;
int m, t; // max turn
int px, py;
int turn = 0; // 현재 턴

void mPrint()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int cnt = 0;
            for (int k = 0; k < 8; k++)
            {
                cnt += monster[turn][i][j][k];
            }
            cout << cnt << " ";
        }
        cout << "\n";
    }
}

bool inRange(int x, int y)
{
    return 0 <= x && x < 4 && 0 <= y && y < 4;
}

void copym()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int d = 0; d < 8; d++)
            {
                egg[turn][i][j][d] = monster[turn - 1][i][j][d];
            }
        }
    }
}

void movem()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int d = 0; d < 8; d++)
            {
                int sign = 0;
                for (int k = 0; k < 8; k++)
                {
                    int td = (d + k) % 8;
                    int nx = i + dx[td]; int ny = j + dy[td];
                    if (!inRange(nx,ny) || dead[nx][ny] >= turn
                    || (nx == px && ny == py)) continue;
                    monster[turn][nx][ny][td] += monster[turn-1][i][j][d];
                    sign = 1;
                    break;
                }
                if (sign == 0)
                {
                    monster[turn][i][j][d] += monster[turn-1][i][j][d];
                }
            }
        }
    }
}

void movep()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            visited[i][j] = false;
        }
    }

    int maxkill = -1;
    int maxdir[3] = {0,0,0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int ii = 0; ii < 4; ii++)
                {
                    for (int jj = 0; jj < 4; jj++)
                    {
                        visited[ii][jj] = false;
                    }
                }
                int dir[3] = {i,j,k};
                int tempkill = 0;
                int x = px; int y = py;
                int sig = 0;
                for (int c = 0; c < 3; c++)
                {
                    x = x + pdx[dir[c]]; y = y + pdy[dir[c]];
                    //cout << x << " " << y << ": x, y\n";
                    if (!inRange(x,y))
                    {
                        sig = 1; break;
                    }
                    if (visited[x][y]) continue;
                    for (int z = 0; z < 8; z++)
                    {
                        tempkill += monster[turn][x][y][z];
                    }
                    visited[x][y] = true;
                }
                if (sig == 1) continue;
                if (tempkill > maxkill)
                {
                    maxkill = tempkill;
                    maxdir[0] = i; 
                    maxdir[1] = j; 
                    maxdir[2] = k;
                    //cout << i << " " << j << " " << k << "\n";
                }

            }
        }
    }
    //cout << maxdir[0] << " " << maxdir[1] << " " << maxdir[2] <<"\n";
    //cout << maxkill;
    for (int i = 0; i < 3; i++)
    {
        px = px + pdx[maxdir[i]]; py = py + pdy[maxdir[i]];
        for (int j = 0; j < 8; j++)
        {
            monster[turn][px][py][j] = 0;
        }
        dead[px][py] = turn+2;
    }
    //cout << "px py: "<< px << " " << py;
}

void birth()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                monster[turn][i][j][k] += egg[turn][i][j][k];
            }
        }
    }
}

void simulate()
{
    // 몬스터 복제
    copym();
    // 몬스터 이동
    movem();
    //();
    //cout << "\n";
    // 팩맨 이동
    movep();
    //cout << "이동 후 \n";
    //mPrint();
    //cout <<"\n";
    // 알 부화
    birth();
}

int main() {
    cin >> m >> t;
    cin >> px >> py; px--; py--;
    for (int i = 0; i < m; i++)
    {
        int r,c,d;
        cin >> r >> c >> d; r--; c--; d--;
        monster[0][r][c][d]++;
    }

    turn = 0;
    while (turn < t)
    {
        turn++;
        simulate();
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                ans += monster[t][i][j][k];
            }
        }
    }
    cout << ans;
    return 0;
}