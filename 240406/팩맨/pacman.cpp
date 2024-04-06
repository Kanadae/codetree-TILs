#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define MAX_T 25
#define dir 8
#define pdir 4
#define max_decay 2
int m_dx[dir] = { -1,-1,0,1,1,1,0,-1 };
int m_dy[dir] = { 0,-1,-1,-1,0,1,1,1 };
int p_dx[pdir] = { -1,0,1,0 };
int p_dy[pdir] = { 0,-1,0,1 };
int n = 4;
int m, t;
int monster[MAX_T + 1][4][4][dir];
int dead[4][4][max_decay + 1];
int px, py;
int turn = 1;

bool inRange(int x, int y)
{
    if (0 <= x && x < 4 && 0 <= y && y < 4) return true;
    return false;
}

bool canGo(int x, int y)
{
    if (inRange(x, y) && dead[x][y][0] == 0 && dead[x][y][1] == 0
        && !(x == px && y == py)) return true;
    return false;
}

void Copy()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int d = 0; d < dir; d++)
            {
                monster[turn][i][j][d] += monster[turn - 1][i][j][d];
            }
        }
    }
}

tuple<int, int, int> mon_move(int x, int y, int d)
{
    for (int i = 0; i < dir; i++)
    {
        int dr = (d + i + dir) % dir;
        int nx = x + m_dx[dr];
        int ny = y + m_dy[dr];
        if (canGo(nx, ny))
        {
            return make_tuple(nx, ny, dr);
        }
    }
    return make_tuple(x, y, d);
}

void move_m()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int d = 0; d < dir; d++)
            {
                int x, y, di;
                tie(x, y, di) = mon_move(i, j, d);
                monster[turn][x][y][di] += monster[turn - 1][i][j][d];
            }
}

int kill_cnt(int i, int j, int k)
{
    int pr = px; int pc = py;
    int direc[] = { i,j,k };
    int kill = 0;
    vector<pair<int, int>> vec;
    for (int d = 0; d < 3; d++)
    {
        pr = pr + p_dx[direc[d]];
        pc = pc + p_dy[direc[d]];
        if (!inRange(pr, pc)) return -1;
        if (find(vec.begin(), vec.end(), make_pair(pr, pc)) == vec.end())
        {
            for (int z = 0; z < dir; z++)
            {
                kill += monster[turn][pr][pc][z];
            }
            vec.push_back(make_pair(pr, pc));
        }
    }
    return kill;
}
tuple<int,int,int> p_kill()
{
    int max_kill = -1;
    int d1, d2, d3;
    for (int i = 0; i < pdir; i++)
        for (int j = 0; j < pdir; j++)
            for (int k = 0; k < pdir; k++)
            {
                int temp_kill = kill_cnt(i, j, k);
                if (max_kill < temp_kill)
                {
                    max_kill = temp_kill;
                    d1 = i; d2 = j; d3 = k;
                }
            }
    return make_tuple(d1, d2, d3);
}

void doKill()
{
    int d1, d2, d3;
    tie(d1, d2, d3) = p_kill();
    int di[] = { d1,d2,d3 };
    for (int i = 0; i < 3; i++)
    {
        px = px + p_dx[di[i]];
        py = py + p_dy[di[i]];
        for (int k = 0; k < dir; k++)
        {
            dead[px][py][max_decay] += monster[turn][px][py][k];
            monster[turn][px][py][k] = 0;
        }
    }
}

void do_decay()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < max_decay; k++)
            {
                dead[i][j][k] = dead[i][j][k + 1];
            }
            dead[i][j][max_decay] = 0;
        }
    }
}

void simulation()
{
    move_m();
    doKill();
    do_decay();
    Copy();
}

int main() {
    cin >> m >> t;
    cin >> px >> py;
    px--; py--;
    for (int i = 0; i < m; i++)
    {
        int r, c, d;
        cin >> r >> c >> d;
        r--; c--; d--;
        monster[0][r][c][d]++;
    }

    while (turn <= t)
    {
        simulation();
        turn++;
    }

    int ans = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < dir; k++)
                ans += monster[t][i][j][k];

    cout << ans;
    return 0;
}