#include <iostream>
using namespace std;
int n, m;
int map[16][16];
int nut[16][16]; // 영양제
int temp_nut[16][16];

int temp[16][16];
int dx[9] = { 0, 0, -1, -1, -1, 0 ,1, 1, 1 };
int dy[9] = { 0, 1, 1, 0, -1, -1, -1, 0, 1 };

int ddx[4] = { -1,1,1,-1 };
int ddy[4] = { 1,1,-1,-1 };

pair<int, int> rule[101];

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
        cin >> rule[i].first >> rule[i].second;
        // first : 이동 방향 second : 이동 거리
    }

    nut[n - 1][0] = 1;
    nut[n - 1][1] = 1;
    nut[n - 2][0] = 1;
    nut[n - 2][1] = 1;

    int year = 0;
    int d, dist; // 방향, 거리
 
    while (m--)
    {
        
        d = rule[year].first;
        dist = rule[year].second;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (nut[i][j] != 1) continue;
                int x = i; int y = j;
                for (int k = 0; k < dist; k++)
                {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (0 > nx) x = n - 1;
                    else if (nx >= n) x = 0;
                    else
                    {
                        x = nx;
                    }
                    if (0 > ny) y = n - 1;
                    else if (ny >= n) y = 0;
                    else y = ny;
                }
                nut[i][j] = 0;
                temp[x][y] = 1;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                nut[i][j] = temp[i][j];
                temp[i][j] = 0;
            }
        }

        

        

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (nut[i][j] == 1)
                {
                    map[i][j] += 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {   
                if (nut[i][j] != 1) continue;
                int cnt = 0;
                for (int k = 0; k < 4; k++)
                {
                    int x = i + ddx[k];
                    int y = j + ddy[k];
                    if (0 > x || x >= n || 0 > y || y >= n) continue;
                    else if (map[x][y] >= 1) cnt++;
                }
                map[i][j] += cnt;
            }
        }

        

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (nut[i][j] == 1) continue;
                if (map[i][j] >= 2)
                {
                    map[i][j] -= 2;
                    temp_nut[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                nut[i][j] = temp_nut[i][j];
                temp_nut[i][j] = 0;
            }
        }

        year++;

    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans += map[i][j];
        }
    }

    cout << ans;
    return 0;
}