#include <iostream>
using namespace std;

int arr[101][101];

int main() {
    int n, m;
    cin >> n >> m;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int d = 1;
    int cnt = 1;
    int r = 1, c = 1;
    int x,y;
    while (cnt <= n*m)
    {
        arr[r][c] = cnt++;
        
        x = r + dx[d];
        y = c + dy[d];
        if (1 <= x && x <= n && 1 <= y && y <= m && arr[x][y] == 0)
        {
            r = x;
            c = y;
        } else {
            d = (d+3) % 4;
            r = r + dx[d];
            c = c + dy[d];
        }

    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <=m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}