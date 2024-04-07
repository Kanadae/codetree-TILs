#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int n, m;
int map[15][15]; // 0이면 빈칸, 1이면 베이스캠프, 2면 아무도 갈 수 없는곳
pair<int, int> cvs_list[30]; // 원하는 편의점 위치
pair<int, int> people[30]; // 사람들 위치 관리

int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };
bool visited[15][15];
queue<pair<int, int>> q;
int step[15][15];
int cur_t = 0;

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool canGo(int x, int y)
{
    return inRange(x, y) && map[x][y] != 2 && !visited[x][y];
}

void bfs()
{
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!canGo(nx, ny)) continue;
            visited[nx][ny] = true;
            step[nx][ny] = step[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
}

void init()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
            step[i][j] = 0;
        }
}

void Move()
{
    for (int i = 0; i < m; i++)
    {
        init();
        if (people[i] == make_pair(-1, -1)) break;
        if (people[i] == cvs_list[i]) continue;
        int goal_x = cvs_list[i].first;
        int goal_y = cvs_list[i].second;
        int min_dist = INT_MAX;
        int min_x = -1; int min_y = -1;
        int x = people[i].first;
        int y = people[i].second;
        q.push(make_pair(goal_x, goal_y));
        visited[goal_x][goal_y] = true;
        step[goal_x][goal_y] = 0;
        bfs();
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (inRange(nx, ny) && visited[nx][ny] == true)
            {
                if (nx == goal_x && ny == goal_y)
                {
                    min_x = goal_x; min_y = goal_y;
                    break;
                }
                if (min_dist > step[nx][ny])
                {
                    min_dist = step[nx][ny];
                    min_x = nx; min_y = ny;
                }
            }
        }
        
        people[i] = make_pair(min_x, min_y);
        init();
    }

    for (int i = 0; i < m; i++)
    {
        if (people[i] == cvs_list[i]) map[people[i].first][people[i].second] = 2;
    }
}

void goCamp()
{
    if (cur_t >= m) return;
    int wx = cvs_list[cur_t].first;
    int wy = cvs_list[cur_t].second;
    q.push(make_pair(wx, wy));
    init();
    visited[wx][wy] = true;
    bfs();
    int min_dist = INT_MAX;
    int min_x = -1; int min_y = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] != 1 || !visited[i][j]) continue;
            if (step[i][j] < min_dist)
            {
                min_dist = step[i][j];
                min_x = i; min_y = j;
            }
        }
    }
   
    people[cur_t] = make_pair(min_x, min_y);
    map[min_x][min_y] = 2;
    init();
}

void simulate()
{
    Move();
    goCamp();

}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        cvs_list[i] = make_pair(x - 1, y - 1);
        people[i] = make_pair(-1, -1);
    }

    while (true)
    {
        simulate();
        cur_t++;
        int sig = 0;
        for (int i = 0; i < m; i++)
        {
            if (people[i] != cvs_list[i])
            {
                sig = 1;
                break;
            }
        }
        if (!sig) break;
    }
    cout << cur_t;

}