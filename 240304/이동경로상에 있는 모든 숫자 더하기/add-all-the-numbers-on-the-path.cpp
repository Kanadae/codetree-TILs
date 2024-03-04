#include <iostream>
#include <cstring>
using namespace std;
int arr[100][100];
int main() {
    int N, T;
    string str;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int d = 3;
    cin >> N >> T;
    cin >> str;
    int len = str.length();
    int r = N / 2;
    int c = r;
    int x, y;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
        }
    }
    int sum = arr[r][c];

    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'F')
        {
            x = r + dx[d];
            y = c + dy[d];
            if (0 <= x && x < N && 0 <= y && y < N)
            {
                r = x;
                c = y;
                //cout << arr[r][c] << endl;
                sum += arr[r][c];
            }
        } else if (str[i] == 'R')
        {
            d = (d + 1) % 4;
        } else if (str[i] == 'L')
        {
            d = (d + 3) % 4;
        }
    }

    cout << sum;
    return 0;
}