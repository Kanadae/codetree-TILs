#include <iostream>
#include <queue>
using namespace std;
int n, qq, l;
int n2;
int map[64][64];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int new_map[64][64];
bool visited[64][64];
queue<pair<int,int>> q;
int icegroup = 0;
int tempice = 0;

bool inRange(int x, int y)
{
    return 0 <= x && x < n2 && 0 <= y && y < n2;
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
            if (!inRange(nx,ny)) continue;
            if (visited[nx][ny]) continue;
            if (map[nx][ny] <= 0) continue;
            q.push(make_pair(nx,ny));
            visited[nx][ny] = true;
            tempice++;
        }
    }
}

void rotate(int sx, int sy, int small_l)
{
    // 좌측 상단
    for (int i = sx; i < sx + small_l; i++)
    {
        for (int j = sy; j < sy + small_l; j++)
        {
            new_map[i][j+small_l] = map[i][j];
        }
    }

    // 우측 상단
    for (int i = sx; i < sx + small_l; i++)
    {
        for (int j = sy + small_l; j < sy + small_l * 2; j++)
        {
            new_map[i+small_l][j] = map[i][j];
        }
    }

    // 좌측 하단
    for (int i = sx + small_l; i < sx + small_l * 2; i++)
    {
        for (int j = sy; j < sy + small_l; j++)
        {
            new_map[i-small_l][j] = map[i][j];
        }
    }

    // 우측 하단
    for (int i = sx + small_l; i < sx + small_l * 2; i++)
    {
        for (int j = sy + small_l; j < sy + small_l * 2; j++)
        {
            new_map[i][j-small_l] = map[i][j];
        }
    }

}

void melt()
{
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (map[i][j] == 0)
            {
                new_map[i][j] = 0; continue;
            }
            int icy = 0;
            for (int dir = 0; dir < 4; dir++)
            {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (!inRange(nx,ny)) continue;
                if (map[nx][ny] > 0) icy++;
            }
            if (icy >= 3)
            {
                new_map[i][j] = map[i][j];
            } else new_map[i][j] = map[i][j] - 1;
        }
    }

    for (int i = 0; i < n2; i++)
        for (int j = 0; j < n2; j++)
        {
            map[i][j] = new_map[i][j];
            new_map[i][j] = 0;
        }
}

void Print()
{
    cout << "\n";
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void simulate()
{
    int l2 = 1 << l; // 2 ^ level
    int small_l = 1 << (l-1); // 2 ^ (level-1)
    // 사각형 쪼개기
    for (int i = 0; i < n2; i += l2)
    {
        for (int j = 0; j < n2; j += l2)
        {
            rotate(i,j,small_l);
        }
    }
    
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            map[i][j] = new_map[i][j];
            new_map[i][j] = 0;
        }
    }
}

int main() {
    cin >> n >> qq;
    n2 = 1 << n;
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < qq; i++)
    {
        cin >> l;
        if (l != 0)
            simulate();
        //Print();
        melt();
        //cout << "melt\n";
        //Print();
    }

    int ice = 0; 
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            ice += map[i][j];
        }
    }

    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (visited[i][j]) continue;
            if (map[i][j] == 0) continue;
            tempice = 1;
            q.push(make_pair(i,j));
            visited[i][j] = true;
            bfs();
            if (tempice > icegroup)
            {
                icegroup = tempice;
            }
        }
    }

    cout << ice << "\n" << icegroup;
    return 0;
}