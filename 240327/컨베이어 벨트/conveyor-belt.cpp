#include <iostream>
using namespace std;

int n, t;
int map[2][201];
int temp[2];

int main() {
    cin >> n >> t;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    while (t--)
    {
        temp[0] = map[0][n-1];
        temp[1] = map[1][n-1];
        for (int i = n - 1; i > 0; i--)
        {
            swap(map[0][i],map[0][i-1]);
        }

        for (int i = n-1; i > 0; i--)
        {
            swap(map[1][i],map[1][i-1]);
        }
        map[1][0] = temp[0];
        map[0][0] = temp[1];
    }
    for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    return 0;
}