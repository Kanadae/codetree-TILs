#include <iostream>
using namespace std;
int n, r, c;
int map[101][101];

int main() {
    cin >> n >> r >> c;
    r--; c--;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    cout << map[r][c] << " ";
    int sig = 1;
    int max = 0;
    int max_x, max_y;
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    while (sig)
    {
        sig = 0;
        for (int i = 0; i < 4; i++)
        {
            int x = r + dx[i];
            int y = c + dy[i];
            if (0 > x || x >= n || 0 > y || y >= n) continue;
            if (map[r][c] < map[x][y]) {
                max = map[x][y];
                sig = 1;
                max_x = x;
                max_y = y;
                break;
            }
        }
        if (sig == 0) break;
        r = max_x;
        c = max_y;
        cout << map[r][c] << " ";
    }
    return 0;
}