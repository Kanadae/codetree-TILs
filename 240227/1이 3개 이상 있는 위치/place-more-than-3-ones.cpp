#include <iostream>
using namespace std;


int arr[101][101];
int main() {
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,-1,0,1};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
           cin >> arr[i][j];
        }
    }
    int x, y;
    int tx, ty;
    int three = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
           x = i;
           y = j;
           for (int k = 0; k < 4; k++)
           {
                tx = x + dx[k];
                ty = y + dy[k];
                if ((0<=tx && tx <= n && 0 <= ty && ty <= n) && arr[tx][ty]==1)
                {
                    three++;
                }
           }
           if (three >= 3) cnt++;
           three = 0;
        }
    }

    cout << cnt;

    return 0;
}