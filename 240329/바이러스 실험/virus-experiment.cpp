#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, k;
int map[11][11];
int copy_map[11][11];
vector<int> virus[11][11]; // 나이 저장, 오름차순
int vir[11][11]; // 바이러스 개수
vector<pair<int, int>> v_xy; // 바이러스 좌표
int nut[11][11];
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> nut[i][j];
            map[i][j] = 5;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int r, c, age;
        cin >> r >> c >> age;
        r--; c--;
        virus[r][c].push_back(age);
        v_xy.push_back(make_pair(r, c));
        vir[r][c]++;
    }

    while (k--)
    {
        for (int i = 0; i < v_xy.size(); i++)
        {
            int x = v_xy[i].first;
            int y = v_xy[i].second;
            sort(virus[x][y].begin(), virus[x][y].end());
            for (int j = 0; j < virus[x][y].size(); j++)
            {
                if (map[x][y] < virus[x][y][j])
                {
                    virus[x][y].erase(virus[x][y].begin() + j);
                    j--;
                    
                    continue;
                }

                map[x][y] -= virus[x][y][j];
                virus[x][y][j]++;
            }
        }
        
        for (int i = 0; i < v_xy.size(); i++)
        {
            int x = v_xy[i].first;
            int y = v_xy[i].second;
            
            for (int j = 0; j < virus[x][y].size(); j++)
            {
                if (virus[x][y][j] % 5 == 0)
                {
                    for (int d = 0; d < 8; d++)
                    {
                        int new_x = x + dx[d];
                        int new_y = y + dy[d];
                        if (0 > new_x || new_x >= n || 0 > new_y || new_y >= n) continue;
                        vir[new_x][new_y]++;
                        v_xy.push_back(make_pair(new_x, new_y));
                        virus[new_x][new_y].push_back(1);
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                map[i][j] += nut[i][j];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (virus[i][j].size() == 0) continue;
            ans += virus[i][j].size();
        }
    }

    cout << ans;
    return 0;
}