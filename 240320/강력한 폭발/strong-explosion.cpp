#include <iostream>
#include <vector>
using namespace std;
int n;
int map[21][21];
int cnt = 0;
int max_cnt = 0;
int bomb = 0;
vector<pair<int, int>> b;
vector<int> vec;
int color[21][21];
int a = 1;
void calc()
{
    for (int i = 0; i < bomb; i++)
    {
        int x = b[i].first;
        int y = b[i].second;
        if (vec[i] == 0)
        {
            if (x - 2 >= 0) color[x - 2][y] = 1;
            if (x - 1 >= 0) color[x - 1][y] = 1;
            if (x + 2 < n) color[x + 2][y] = 1;
            if (x + 1 < n) color[x + 1][y] = 1;

        }
        else if (vec[i] == 1)
        {
            if (x - 1 >= 0) color[x - 1][y] = 1;
            if (x + 1 < n) color[x + 1][y] = 1;
            if (y - 1 >= 0) color[x][y - 1] = 1;
            if (y + 1 < n) color[x][y + 1] = 1;
        }
        else if (vec[i] == 2)
        {
            if ((x - 1 >= 0) && (y - 1 >= 0)) color[x - 1][y - 1] = 1;
            if ((x - 1 >= 0) && (y + 1 <= n)) color[x - 1][y + 1] = 1;
            if ((x + 1 < n) && (y - 1 >= 0)) color[x + 1][y - 1] = 1;
            if ((x + 1 < n) && (y + 1 < n)) color[x + 1][y + 1] = 1;
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (color[i][j] == 1)
            {
                if (map[i][j] == 0)
                {
                    cnt++;
                }
                color[i][j] = 0;
            }
        }
    }
    if (max_cnt < cnt)
    {
        max_cnt = cnt;
    }
    cnt = 0;
}

void choose(int cur)
{
    if (cur == bomb)
    {
        calc();
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        vec.push_back(i);
        choose(cur + 1);
        vec.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                b.push_back(make_pair(i, j));
                bomb++;
            }
        }
    }
    choose(0);
    cout << max_cnt + bomb;
    return 0;
}