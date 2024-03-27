#include <iostream>
using namespace std;
int n , m , q;
int map[101][101];
int temp_map[101][101];
int temp[4];
int main() {
    cin >> n >> m >> q;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int d;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    while (q--)
    {
        int r1,c1,r2,c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        temp[0] = map[r1][c2];
        for (int i = c2; i > c1; i--)
        {
            map[r1][i] = map[r1][i-1];
        }
        temp[1] = map[r2][c2];
        for (int i = r2; i > r1; i--)
        {
            map[i][c2] = map[i-1][c2];
        }
        temp[2] = map[r2][c1];
        for (int i = c1; i < c2; i++)
        {
            map[r2][i] = map[r2][i+1];
        }
        temp[3] = map[r1][c1];
        for (int i = r1; i < r2; i++)
        {
            map[i][c1] = map[i+1][c1];
        }
        map[r1+1][c2] = temp[0];
        map[r2][c2-1] = temp[1];
        map[r2-1][c1] = temp[2];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                temp_map[i][j] = map[i][j];
            }
        }
        int sum = 0;
        int cnt = 0;

        for (int i = r1; i <= r2; i++)
        {
            for (int j = c1; j <= c2; j++)
            {
                sum = temp_map[i][j];
                cnt = 1;
                for (int k = 0; k < 4; k++)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (0 > x || x >= n || 0 > y || y >= m) continue;
                    sum += temp_map[x][y];
                    cnt++;
                }
                sum = sum / cnt;
                map[i][j] = sum;
            }
        }
    }
    
    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << map[i][j] << " ";
            }
            cout << "\n";
        }
    return 0;
}