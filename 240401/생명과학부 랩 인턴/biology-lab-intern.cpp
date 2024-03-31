#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int n, m, k;
int ans;
vector<pair<int, int>> vec[101][101]; // 각 위치에 곰팡이 크기 / 속도
vector<tuple<int, int, int>> t[101][101];
vector<tuple<int, int, int>> new_t[101][101];
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, 1, -1 };
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int x, y, s, d, b; // x,y는 위치, s는 속도, d 방향 b 크기
        cin >> x >> y >> s >> d >> b;
        x--; y--;
        t[x][y].push_back(make_tuple(b, s, d)); // 크기 속도 방향 순서
    }
    int obs = 0;
    while (obs < m)
    {
        
        for (int i = 0; i < n; i++)
        {
            if (t[i][obs].size() != 0)
            {
                int big, rate, dir;
                tie(big, rate, dir) = t[i][obs][0];
         
                ans += big;
                t[i][obs].pop_back();
                break;
            }
        }
        int big, rate, dir;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (t[i][j].size() == 0) continue;
                int big, rate, dir;
                tie(big, rate, dir) = t[i][j][0];
                int x = i; int y = j;
                for (int r = 0; r < rate; r++)
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (0 > nx || nx >= n || 0 > ny || ny >= m)
                    {
                        if (dir == 1) dir = 2;
                        else if (dir == 2) dir = 1;
                        else if (dir == 3) dir = 4;
                        else if (dir == 4) dir = 3;
                        nx = x + dx[dir];
                        ny = y + dy[dir];
                    }
                    x = nx;
                    y = ny;
                }
                new_t[x][y].push_back(make_tuple(big, rate, dir));
                t[i][j].clear();
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sort(new_t[i][j].rbegin(), new_t[i][j].rend());
                if (new_t[i][j].size() == 0) continue;
                t[i][j].push_back(new_t[i][j][0]);
                new_t[i][j].clear();
            }
        }
        obs++;
    }
    cout << ans;
    return 0;
}