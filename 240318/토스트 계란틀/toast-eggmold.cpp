#include <iostream>
#include <vector>
using namespace std;
int egg[51][51];
vector<int> check[51][51];
int sum = 0;

int cc = 0;
int dx[2] = { 0, 1 }; // 동남
int dy[2] = { 1, 0 };

void iter(int i, int j)
{
    if (egg[i][j] == -1) return;
    cc++;
    sum += egg[i][j];
    egg[i][j] = -1;

    int d;
    for (int k = check[i][j].size(); k > 0; k--)
    {
        d = check[i][j].back();
        check[i][j].pop_back();
        int x = i + dx[d];
        int y = j + dy[d];
        iter(x, y);
    }

}

int main() {
    int n, L, R;
    cin >> n >> L >> R;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> egg[i][j];
        }
    }
    int sig = 1;
    int d;
    int x, y;
    int r, c;
    int diff;
    int occur = 0;
    int cnt = 0;
    while (sig)
    {
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                r = i; c = j;
                for (int k = 0; k < 2; k++)
                {
                    x = r + dx[k];
                    y = c + dy[k];
                    if (0 <= x && x < n && 0 <= y && y < n)
                    {
                        diff = abs(egg[i][j] - egg[x][y]);
                        if (diff >= L && diff <= R)
                        {
                            check[i][j].push_back(k);
                            occur++;
                        }
                    }
                }

            }
        }
        if (!occur) break;
        else occur = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!check[i][j].size()) continue;
                iter(i, j);
                //cout << "sum: " << sum << " " << "CC: " << cc << endl;
                int aver = sum / cc;
                for (int ii = 0; ii < n; ii++)
                {
                    for (int jj = 0; jj < n; jj++)
                    {
                        if (egg[ii][jj] == -1) egg[ii][jj] = aver;
                    }
                }
                sum = 0; cc = 0;
            }
        }

        cnt++;
        
    }
  
    cout << cnt;
    return 0;
}