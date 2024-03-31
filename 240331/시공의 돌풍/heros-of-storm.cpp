#include <iostream>
using namespace std;

int dx[4] = {0,1,0,-1}; // 동남서북
int dy[4] = {1,0,-1,0}; // 시계방향 +1 반시계 +3
int n,m,t;
int map[51][51];
int temp_map[51][51];
pair<int,int> start[2];
int s = 0;
int temp[4];

int main() {
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == -1)
            {
                start[s++] = make_pair(i,j);
            }
        }
    }

while (t--)
{
    // 맵에서 깎이는것만 맵에 포함. temp_map에는 확산 먼지 양만
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int dust = map[i][j] / 5;
            int cnt = 0;
            for (int d = 0; d < 4; d++)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if (0 > x || x >= n || 0 > y || y >= m) continue;
                if (map[x][y] == -1) continue;
                else {
                    cnt++;
                    temp_map[x][y] += dust;
                }
            }
            map[i][j] -= dust * cnt; 
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            map[i][j] += temp_map[i][j];
            temp_map[i][j] = 0;
        }
    }

    
    int r = start[0].first;
    int c = start[0].second;
    temp[0] = map[r][m-1];
    // 반시계 회전
    for (int i = m-1; i > 1; i--)
    {
        map[r][i] = map[r][i-1];
    }
    map[r][1] = 0;
    temp[1] = map[0][m-1];

    for (int i = 0; i < r; i++)
    {
        map[i][m-1] = map[i+1][m-1];
    }
    map[r-1][m-1] = temp[0];

    temp[2] = map[0][0];
    for (int i = 0; i < m - 1; i++)
    {
        map[0][i] = map[0][i+1];
    }
    map[0][m-2] = temp[1];

    for (int i = r - 1; i > 0; i--)
    {
        map[i][0] = map[i-1][0];
    }
    map[1][0] = temp[2];

    // 시계
    r = start[1].first;
    c = start[1].second;
    temp[0] = map[r][m-1]; // r행 맨 마지막 원소
    for (int i = m-1; i > 1; i--)
    {
        map[r][i] = map[r][i-1];
    }
    map[r][1] = 0;

    temp[1] = map[n-1][m-1]; // 맨 끝 맨 오른쪽
    for (int i = n-1; i > r; i--)
    {
        map[i][m-1] = map[i-1][m-1];
    }
    map[r+1][m-1] = temp[0];

    temp[2] = map[n-1][0];
    for (int i = 0; i < m-1; i++)
    {
        map[n-1][i] = map[n-1][i+1];
    }
    map[n-1][m-2] = temp[1];

    for (int i = r + 1; i < n - 1; i++)
    {
        map[i][0] = map[i+1][0];
    }

    map[n-2][0] = temp[2];

}

int ans = 0;
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < m; j++)
    {
        if (map[i][j] == -1) continue;
        ans += map[i][j];
    }
}
cout << ans;
    return 0;
}