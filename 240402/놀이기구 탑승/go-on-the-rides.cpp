#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> vec[401];
int turn[401];
int map[21][21];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int main() {
    cin >> n;
    for (int i = 0; i < n * n; i++)
    {
        int a, b;
        cin >> a;
        a--;
        turn[i] = a;
        for (int j = 0; j < 4; j++)
        {
            cin >> b;
            b--;
            vec[a].push_back(b);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[i][j] = -1; // -1로 맵 초기화
        }
    }
    

    for (int i = 0; i < n * n; i++)
    {
        int t = turn[i]; // vec[t][0]~vec[t][3] 좋아하는 애
        int like = 0;
        int space = 0;
        int r = -2,c = -2;
        for (int j = 0; j < n; j++) // j가 행, k가 열
        {
            for (int k = 0; k < n; k++)
            {
                if (map[j][k] != -1) continue; // 이미 누가 앉은 자리

                int temp_like = 0;
                int temp_space = 0;
                for (int d = 0; d < 4; d++)
                {
                    int x = j + dx[d];
                    int y = k + dy[d];
                    if (0 > x || x >= n || 0 > y || y >= n) continue;
                    if (map[x][y] == -1)
                    {
                        temp_space++;
                        continue;
                    }
                    for (int l = 0; l < 4; l++)
                    {
                        if (map[x][y] == vec[t][l]) temp_like++;
                    }
                }
                if (temp_like > like)
                {
                    like = temp_like;
                    space = temp_space;
                    r = j; c = k; continue;
                }
                if (temp_like == like)
                {
                    if (temp_space > space)
                    {
                        space = temp_space;
                        r = j; c = k;
                    }
                }
                if (map[j][k] == -1 && r == -2)
                {
                    r = j; c = k;
                }
            }
        }
        map[r][c] = t;
        
        
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int t = map[i][j];
            int like = 0;
            for (int d = 0; d < 4; d++)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if (0 > x || x >= n || 0 > y || y >= n) continue;
                for (int a = 0; a < 4; a++)
                {
                    if (map[x][y] == vec[t][a])
                    {
                        like++;
                        break;
                    }
                }
            }

            if (like == 1) ans += 1;
            else if (like == 2) ans += 10;
            else if (like == 3) ans += 100;
        }
        
    }

    cout << ans;
    return 0;
}