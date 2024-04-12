#include <iostream>
#include <tuple>
using namespace std;
int n, m, k, c; // 격자 크기, 년 수, 확산 범위, 제초제 수명
int map[1001][21][21]; // 턴 수, 좌표
int r[21][21]; // 제초제 수명
int tdx[4] = {0,-1,0,1};
int tdy[4] = {1,0,-1,0}; // 인접 나무
int rdx[4] = {-1,1,1,-1};
int rdy[4] = {-1,-1,1,1}; // 제초제 방향
int turn = 1;
int ans = 0;

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[turn][i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void grow()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[turn-1][i][j] <= 0) continue;
            int tree = 0;
            for (int d = 0; d < 4; d++)
            {
                int nx = i + tdx[d];
                int ny = j + tdy[d];
                if (!inRange(nx,ny)) continue;
                if (map[turn-1][nx][ny] > 0) tree++;
            }
            map[turn-1][i][j] += tree;
        }
    }
}

void increase()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[turn][i][j] += map[turn-1][i][j];
            if (map[turn-1][i][j] <= 0) continue;
            int tree = map[turn-1][i][j];
            int space = 0;
            for (int z = 0; z < 4; z++)
            {
                int nx = i + tdx[z];
                int ny = j + tdy[z];
                if (!inRange(nx,ny)) continue;
                if (r[nx][ny] > 0) continue;
                if (map[turn-1][nx][ny] == 0)
                {
                    space++;
                }
            }
            if (space == 0) continue;
            tree = tree / space;
            for (int z = 0; z < 4; z++)
            {
                int nx = i + tdx[z];
                int ny = j + tdy[z];
                if (!inRange(nx,ny)) continue;
                if (r[nx][ny] > 0) continue;
                if (map[turn-1][nx][ny] == 0)
                {
                    map[turn][nx][ny] += tree;
                }
            }
        }
    }

}

pair<int,int> choosespace()
{
    int maxkill = -1;
    int mx = 0, my = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tempkill = 0;
            if (map[turn][i][j] <= 0)
            {
                if (maxkill < tempkill)
                {
                    maxkill = tempkill;
                    mx = i; my = j;
                }
                continue;
            }
            tempkill = map[turn][i][j];
            for (int z = 0; z < 4; z++)
            {
                for (int tk = 1; tk <= k; tk++)
                {
                    int nx = i + tk * rdx[z];
                    int ny = j + tk * rdy[z];
                    if (!inRange(nx,ny) || map[turn][nx][ny] == -1
                    || map[turn][nx][ny] == 0) break;
                    tempkill += map[turn][nx][ny];
                }
            }
            if (tempkill > maxkill)
            {
                maxkill = tempkill;
                mx = i; my = j;
                //cout << i << " " << j << "\n";
            }
        }
    }

    return make_pair(mx,my);
}

void Remove(int x, int y)
{
    int killed = 0;
    if (map[turn][x][y] <= 0)
    {
        r[x][y] = c;
        return;
    }
    killed = map[turn][x][y];
    r[x][y] = c;
    map[turn][x][y] = 0;
            for (int z = 0; z < 4; z++)
            {
                for (int tk = 1; tk <= k; tk++)
                {
                    int nx = x + tk * rdx[z];
                    int ny = y + tk * rdy[z];
                    if (!inRange(nx,ny) || map[turn][nx][ny] == -1) break;
                    if (map[turn][nx][ny] == 0)
                    {
                        r[nx][ny] = c; break;
                    }
                    killed += map[turn][nx][ny];
                    map[turn][nx][ny] = 0;
                    r[nx][ny] = c;
                }
            }

    ans += killed;

}

void rdecay()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (r[i][j] > 0) r[i][j]--;
        }
    }
}

void simulate()
{
    // 나무 성장
    grow();
    // 나무 번식
    increase();
    //Print();
    // 칸 선택
    int mx, my;
    tie(mx,my) = choosespace();
    //cout << map[turn][2][2] << " ?";
    //cout << mx << " " << my << "\n";
    // 제초제 수명 단축
    rdecay();
    // 제초제 분사
    Remove(mx,my);
    //Print();
}

int main() {
    cin >> n >> m >> k >> c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[0][i][j];
        }
    }

    while (turn <= m)
    {
        simulate();
        turn++;
    }

    cout << ans;

    return 0;
}