#include <iostream>
using namespace std;
char alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char arr[101][101];
int main() {
    int n, m;
    cin >> n >> m;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int d = 0;
    int cnt = 0;
    int alp;
    int r = 0, c = 0;
    int x,y;
    while (cnt <= n*m)
    {
        alp = cnt % 26;
        if (arr[r][c] == 0) arr[r][c] = alpha[alp];
        cnt++;
        x = r + dx[d];
        y = c + dy[d];
        if (0 <= x && x < n && 0<=y && y < m && arr[x][y] == 0)
        {
            r = x;
            c = y;
        } else {
            d = (d+1) % 4;
            r = r + dx[d];
            c = c + dy[d];
        }

    }
    for (int i = 0; i < n; i++)
    {
        for (int j =0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}