#include <iostream>
using namespace std;
int n, m, q;
int map[101][101];
int sig = 0; // 0이면 left, 1이면 right

void left_shift(int r) // 왼쪽에서 부는 바람
{
    int temp = map[r][m - 1];
    for (int i = m - 1; i > 0; i--)
    {
        swap(map[r][i], map[r][i - 1]);
    }
    map[r][0] = temp;
}

void right_shift(int r) // 오른쪽에서 부는 바람
{
    int temp = map[r][0];
    for (int i = 0; i < m - 1; i++)
    {
        swap(map[r][i], map[r][i + 1]);
    }
    map[r][m - 1] = temp;
}

bool Same(int r, int rr)
{
    for (int i = 0; i < m; i++)
    {
        if (map[r][i] == map[rr][i]) return true;
    }
    return false;
}

int main() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    while (q--)
    {
        int wind;
        char direction;
        cin >> wind >> direction;
        wind--;
        if (direction == 'L')
        {
            sig = 0;
            left_shift(wind);
        }
        else if (direction == 'R') {
            sig = 1;
            right_shift(wind);
        }

        int up = wind;
        int up_sig = sig;
        // Same(wind, wind-1) is true면 wind-1에 ~sig 방향으로 바람
        while (up - 1 >= 0 && Same(up, up - 1))
        {
            if (up_sig == 0) up_sig = 1; else up_sig = 0;
            if (up_sig == 0) left_shift(up - 1);
            else right_shift(up - 1);
            up--;
        }

        while (wind + 1 < n && Same(wind, wind + 1))
        {
            if (sig == 0) sig = 1; else sig = 0;
            if (sig == 0) left_shift(wind + 1);
            else right_shift(wind + 1);
            wind++;
        }

    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}