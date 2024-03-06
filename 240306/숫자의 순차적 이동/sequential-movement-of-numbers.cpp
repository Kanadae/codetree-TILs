#include <iostream>
#include <climits>
using namespace std;
int arr[21][21];
int main() {
    int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int n, m;
    int turn = 1;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    int x, y;
    int tx, ty;
    int idx,idy;
    int temp;
    int max;
    int num = 1;
    int sig = 0;
    while (turn <= m)
    {
        num = 1;
        turn++;
        while (num <= n*n)
        {
            sig = 0;
            for (int i = 0; i < n; i++)
            {
                if (sig == 1) break;
                for (int j = 0; j < n; j++)
                {
                    if (arr[i][j] == num)
                    {
                        idx = i;
                        idy = j;
                        sig = 1;
                        break;
                    }
                }
            }

        max = INT_MIN;
        for (int k = 0; k < 8; k++)
        {
            x = idx + dx[k];
            y = idy + dy[k];
            if (0 <= x && x < n && 0 <= y && y < n)
            {
                if (arr[x][y] > max)
                {
                    max = arr[x][y];
                    tx = x;
                    ty = y;

                }
            }
        }
        temp = arr[idx][idy];
        arr[idx][idy] = max;
        arr[tx][ty] = temp;
        num++;
        }
    }

       for (int i = 0; i < n; i++)
   {
       for (int j = 0; j < n; j++)
       {
           cout << arr[i][j] << " ";
       }
       cout << "\n";
   }


    return 0;
}