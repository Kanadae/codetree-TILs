#include <iostream>
using namespace std;
int arr[101][101];
int main() {
    int n;
    cin >> n;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int d = 0;
    int cnt = 1;
    int r = n / 2;
    int c = r;
    int x,y;
    int td;
    int go = 0;
    arr[r][c] = cnt++;
    r = r + dx[d];
    c = c + dy[d];
    while (cnt <= n*n)
    {
        arr[r][c] = cnt;
        cnt++;
        
        td = (d + 3) % 4;
        x = r + dx[td];
        y = c + dy[td];
        if (arr[x][y] == 0)
        {
            r = x;
            c = y;
            d = td;
            go = 0;
        } else {
            r = r + dx[d];
            c = c + dy[d];
            go++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] <<" ";
        }
        cout << "\n";
    }
    return 0;
}