#include <iostream>
#include <climits>
using namespace std;
int arr[21][21];
int ball[21][21];
int count[21][21];
int main() {
    int n , m, t;
    cin >> n >> m >> t;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    int r,c;
    for (int i = 0; i < m; i++)
    {
        cin >> r >> c;
        r -= 1;
        c -= 1;
        ball[r][c] = 1;
    }
    int d;
    int max = INT_MIN;
    int x, y;
    int tx, ty;
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (ball[j][k] == 0) continue;
                max = INT_MIN;
                for (int l = 0; l < 4; l++)
                {
                    x = j + dx[l];
                    y = k + dy[l];
                    if (0 <= x && x < n && 0 <= y && y < n)
                    {
                        if (arr[x][y] > max){
                            d = l;
                            max = arr[x][y];
                            tx = x;
                            ty = y;
                        }
                    }
                }
                ball[j][k]--;
                count[tx][ty]++;
            }
        }

        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (count[j][k] == 1) ball[j][k] = 1;
                else if (count[j][k] > 1){
                    count[j][k] = 0;
                    ball[j][k] = 0;
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ball[i][j] == 1) cnt++;
        }
    }

    cout << cnt;

    return 0;
}