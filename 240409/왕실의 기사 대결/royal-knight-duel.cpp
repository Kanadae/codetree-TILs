#include <iostream>
#include <queue>
using namespace std;
int l, n, q;
int info[41][41];
int r[31]; int c[31]; int h[31]; int w[31]; int k[31];
int nr[31]; int nc[31]; int nh[31]; int nw[31]; int nk[31];
bool is_move[31];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int damage[31];
int initial_damage[31];

bool tryMove(int idx, int dir)
{
    for (int i = 1; i <= n; i++)
    {
        damage[i] = 0;
        is_move[i] = false;
        nr[i] = r[i];
        nc[i] = c[i];
    }

    queue<int> q;
    is_move[idx] = true;
    q.push(idx);
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        nr[x] += dx[dir];
        nc[x] += dy[dir];
        
        if (nr[x] <= 0 || nr[x] + h[x] - 1 > l || nc[x] <= 0 || nc[x] +
        w[x] - 1 > l) return false;

        for (int i = nr[x]; i <= nr[x] + h[x] - 1; i++)
            for (int j = nc[x]; j <= nc[x] + w[x] - 1; j++)
            {
                if (info[i][j] == 1)
                    damage[x]++;
                if (info[i][j] == 2) return false;
            }

        for (int i = 1; i <= n; i++)
        {
            if (is_move[i] || k[i] <= 0) continue;
            if (r[i] > nr[x] + h[x] - 1 || nr[x] > r[i] + h[i] -1)
                continue;
            if (c[i] > nc[x] + w[x] - 1 || nc[x] > c[i] + w[i] - 1)
                continue;
            q.push(i);
            is_move[i] = true;
        }
    }
    damage[idx] = 0;
    return true;
}

void move(int idx,int dir)
{
    if (k[idx] <= 0) return;

    if (tryMove(idx,dir))
    {
        for (int i = 1; i <= n; i++)
        {
            r[i] = nr[i];
            c[i] = nc[i];
            k[i] -= damage[i];
        }
    }
}

int main() {
    cin >> l >> n >> q;
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            cin >> info[i][j];
    for (int i = 1; i <= n; i++)
    {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        initial_damage[i] = k[i];
    }
        
    for (int i = 1; i <= q; i++)
    {
        int idx, dir;
        cin >> idx >> dir;
        move(idx,dir);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (k[i] > 0){
            ans += initial_damage[i] - k[i];
        }
        
    }

    cout << ans;

    return 0;
}