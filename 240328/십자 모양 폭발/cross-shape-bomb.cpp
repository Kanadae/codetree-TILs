#include <iostream>
using namespace std;
int n;
int map[201][201];
int temp[201];
int bomb;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    int r,c;
    cin >> r >> c;
    r--; c--;

    bomb = map[r][c];
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < bomb; j++)
        {
            int x = r + j*dx[i];
            int y = c + j*dy[i];
            if (0 > x || x >= n || 0 > y || y >= n) continue;
            map[x][y] = 0;
        }
    }   

    int temp_y = n-1;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (map[j][i] != 0)
            {
                temp[temp_y--] = map[j][i]; 
            }
        }

        for (int j = 0; j < n; j++)
        {
            map[j][i] = temp[j];
        }

        for (int j = 0; j < n; j++)
        {
            temp[j] = 0;
        }

        temp_y = n - 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}