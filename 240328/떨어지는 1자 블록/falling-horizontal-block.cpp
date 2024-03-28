#include <iostream>
using namespace std;
int n, length, r;
int map[101][101];

int main() {
    cin >> n >> length >> r;
    r--;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    int stop = n - 1;
    int sig = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = r; j < r+length; j++)
        {
            if (map[i][j] == 1)
            {
                stop = i-1;
                sig = 1;
                break;
            }
        }
        if (sig) break;
    }

    int idx = r;
    for (int i = 0; i < length; i++)
    {
        map[stop][idx++] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}