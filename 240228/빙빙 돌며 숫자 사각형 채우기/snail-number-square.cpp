#include <iostream>
using namespace std;
int arr[101][101];

int main() {
    int n , m, direction;
    int xd[4] = {0, 1, 0, -1};
    int yd[4] = {1, 0, -1, 0};
    direction = 0;
    cin >> n >> m;
    int r = 1, c = 1;
    int nx, ny;
    int cur = 2;
    arr[1][1] = 1;
    while (cur <= n * m)
    {
        nx = r + xd[direction]; ny = c + yd[direction];
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m && arr[nx][ny] == 0)
        {
            r = nx; c = ny;
            arr[r][c] = cur++;
        } else {
            direction = (direction + 1) % 4;
        }

    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}