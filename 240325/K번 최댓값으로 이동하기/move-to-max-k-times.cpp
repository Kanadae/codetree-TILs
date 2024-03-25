#include <iostream>
#include <queue>
using namespace std;
int n,k;
int start_x , start_y;
int map[101][101];
bool visited[101][101];
queue<pair<int, int>> q;
int maxi;
pair<int,int> maxi_locate;
int cur;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    if (map[x][y] >= cur) return false;
    return true;
}

void bfs()
{
    int dx[4] = {0, 1 ,0, -1};
    int dy[4] = {1, 0, -1, 0};
    while (!q.empty())
    {
        int x,y;
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (Cango(new_x,new_y))
            {
                if (maxi < map[new_x][new_y]) {
                    maxi = map[new_x][new_y];
                    maxi_locate = make_pair(new_x,new_y);
                } else if (maxi == map[new_x][new_y])
                {
                    int mx = maxi_locate.first;
                    int my = maxi_locate.second;
                    if (mx > new_x)
                    {
                        maxi_locate = make_pair(new_x,new_y);
                    } else if (mx == new_x)
                    {
                        if (my > new_y) maxi_locate = make_pair(new_x,new_y);
                    }
                }
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x,new_y));
            }
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    cin >> start_x >> start_y;
    start_x--; start_y--;
    int cnt = 0;
    while (cnt < k)
    {
        cur = map[start_x][start_y];
        q.push(make_pair(start_x,start_y));
        bfs();
        if (maxi == 0) break;
        start_x = maxi_locate.first;
        start_y = maxi_locate.second;
        cur = maxi;
       
        maxi = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }
        cnt++;
    }

    cout << ++start_x << " " << ++start_y;
    return 0;
}