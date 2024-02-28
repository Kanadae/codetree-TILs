#include <iostream>
using namespace std;

int main() {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    int N;
    cin >> N;
    int x = 0, y = 0;
    int dir, dist;
    char d;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> d >> dist;
        if (d == 'E') dir = 0;
        if (d == 'S') dir = 1;
        if (d == 'W') dir = 2;
        if (d == 'N') dir = 3;
        for (int j = 0; j < dist; j++)
        {
            x = x + dx[dir];
            y = y + dy[dir];
            cnt++;
            if (x == 0 && y == 0){
                cout << cnt;
                break;
            }
        }
        if (x == 0 && y == 0){
                break;
        }
    }
    if (x!=0 || y!=0) cout << -1;
    return 0;
}