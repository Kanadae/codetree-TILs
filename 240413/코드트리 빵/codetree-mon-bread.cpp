#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m; // 격자 크기, 사람 수
int map[16][16]; // 누가 들어간 베이스 캠프, 도착한 편의점 = 1
vector<pair<int,int>> base;
pair<int,int> cvs_list[31]; // wish cvs
pair<int,int> people[31]; // 사람 위치
bool visited[16][16];
int backx[16][16]; int backy[16][16];
int step[16][16];
int dx[4] = {-1,0,0,1}; // 우선순위
int dy[4] = {0,-1,1,0};
int debugp[16][16];
queue<pair<int,int>> qu;
void Print()
{
    for (int i = 0; i < m; i++)
    {
        int x= people[i].first;
        int y = people[i].second;
        if (x == -1) break;
        debugp[x][y] = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            cout << debugp[i][j] << " ";
            debugp[i][j] = 0;
        }
        cout << "\n";
    }
    cout <<"\n";
}

bool inRange(int x,int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void bfs()
{
    while (!qu.empty())
    {
        int x = qu.front().first;
        int y = qu.front().second;
        qu.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inRange(nx,ny)) continue;
            if (visited[nx][ny] || map[nx][ny]) continue;
            visited[nx][ny] = true;
            qu.push(make_pair(nx,ny));
            step[nx][ny] = step[x][y] + 1;
        }
    }
}

void Move(int t)
{
    for (int i = 0; i < m; i++)
    {
        if (people[i].first == -1) break;
        int wx = cvs_list[i].first; int wy = cvs_list[i].second;
        int cx = people[i].first; int cy = people[i].second;
        if (wx == cx && wy == cy) continue;
        int mindist = 10000000; int minx = 0; int miny = 0;
        for (int d = 0; d < 4; d++)
        {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!inRange(nx,ny)) continue;
            if (map[nx][ny] == 1) continue;
            if (nx == wx && ny == wy)
            {
                minx = nx; miny = ny; break;
            }
            qu.push(make_pair(nx,ny));
            visited[nx][ny] = true;
            bfs();
            if (step[wx][wy] == 0)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        visited[i][j] = false;
                        step[i][j] = 0;
                    }
                }
                continue;
            }
            if (step[wx][wy] < mindist)
            {
                mindist = step[wx][wy];
                minx = nx; miny = ny;
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    visited[i][j] = false;
                    step[i][j] = 0;
                }
            }
        }
        
        people[i].first = minx; people[i].second = miny;
        if (minx == wx && miny == wy)
        {
            map[minx][miny] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
                step[i][j] = 0;
            }
        }
    }
}

void goCamp(int t)
{
    for (int i = 0; i < n; i++)
    {
        for (int j =0 ; j < n; j++)
        {
            visited[i][j] = false;
            step[i][j] = 0;
        }
    }
    if (t < m)
    {
        int wx = cvs_list[t].first;
        int wy = cvs_list[t].second;
        int nearbase = 0; int mindist = 10000000;
        for (int i = 0; i < base.size(); i++)
        {
            int bx = base[i].first; int by = base[i].second;
            queue<pair<int,int>> q;
            q.push(make_pair(bx,by));
            visited[bx][by] = true;
            while (!q.empty())
            {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int d = 0; d < 4; d++)
                {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (!inRange(nx,ny)) continue;
                    if (map[nx][ny]==1 || visited[nx][ny]) continue;
                    visited[nx][ny] = true;
                    q.push(make_pair(nx,ny));
                    step[nx][ny] = step[x][y] + 1;
                }
            }
            int tempdist = step[wx][wy];
            if (tempdist < mindist)
            {
                mindist = tempdist;
                nearbase = i;
            }
            for (int i = 0; i < n; i ++)
            {
                for (int j = 0; j < n ; j++)
                {
                    visited[i][j] = false;
                    step[i][j] = 0;
                }
            }
        }
        people[t].first = base[nearbase].first;
        people[t].second = base[nearbase].second;
        map[people[t].first][people[t].second] = 1;
        base.erase(base.begin()+nearbase);
    }
}

void simulate(int t)
{
    Move(t);
    goCamp(t);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j< n; j++)
        {
            int temp;
            cin >> temp;
            if (temp == 1)
            {
                base.push_back(make_pair(i,j)); // 베이스캠프 위치 저장
            }
        }
    }
    sort(base.begin(),base.end());
    for (int i = 0; i < m; i++)
    {
        int x,y;
        cin >> x >> y; x--; y--;
        cvs_list[i] = make_pair(x,y);
    }
    for (int i = 0; i < m; i++)
    {
        people[i].first = -1; people[i].second = -1;
    }
    int t = 0;
    int sig = 1;
    while (sig)
    {
        sig = 0;
        simulate(t);
        t++;
        for (int i = 0; i < m; i++)
        {
            if (cvs_list[i].first != people[i].first ||
            cvs_list[i].second != people[i].second)
            {
                sig = 1;
                break;
            }
        }
        //Print();
    }

    cout << t;
    return 0;
}