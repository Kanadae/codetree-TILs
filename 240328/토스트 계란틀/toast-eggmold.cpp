#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int n, l, r;
int map[51][51];
int copy_map[51][51];
int ans;
int eggs;
int egg_cnt;
int sig = 1;
int visited[51][51];
int egg;
queue<pair<int, int>> q;
vector<pair<int, int>> loc;

bool canGo(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    return true;
}

bool calc(int a, int b)
{
    int diff = abs(a - b);
    if (diff >= l && diff <= r)
    {
        return true;
    }
    return false;
}

void bfs()
{
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        int x = cur.first;
        int y = cur.second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];

            if (canGo(new_x, new_y) && calc(map[x][y], map[new_x][new_y]))
            {
                sig = 1;
                visited[new_x][new_y] = true;
                
                eggs += map[new_x][new_y];
                egg_cnt++;
             
                loc.push_back(make_pair(new_x, new_y));
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            copy_map[i][j] = map[i][j];
        }
    }
    while (sig)
    {
        sig = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visited[i][j]) continue;
                egg_cnt = 0;
                eggs = 0;
                visited[i][j] = true;
                q.push(make_pair(i, j));
                bfs();
                if (egg_cnt == 0)
                {
                    visited[i][j] = true;
                    continue;
                }
                loc.push_back(make_pair(i, j));
                eggs += map[i][j];
                egg_cnt++;
                
                egg = eggs / egg_cnt;
                
                for (int k = 0; k < loc.size(); k++)
                {
                    int x = loc[k].first;
                    int y = loc[k].second;
                    copy_map[x][y] = egg;
                    
                }
                loc.clear();
            }
        }
       
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                map[i][j] = copy_map[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }

        if (sig == 0) break;
        
        ans++;
    }

    cout << ans << endl;
    return 0;
}