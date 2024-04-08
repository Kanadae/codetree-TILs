#include <iostream>
#include <tuple>
using namespace std;
int n, m, k;
int maze[10][10];
int people[10][10]; // 각 좌표 사람 수
int dx[4] = { -1,1,0,0 }; // 상하좌우
int dy[4] = { 0,0,-1,1 };
pair<int, int> EXIT; // 출구 위치
pair<int, int> NEXT_EXIT;
int next_people[10][10]; // 사람 수
int next_maze[10][10];

int rx[8] = { -1,-1,-1,0,0,1,1,1 };
int ry[8] = { -1,0,1,-1,1,-1,0,1 };
int walk; // 이동횟수
int square_size;
int SX;
int SY;

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void PP()
{
    cout << 8 - k << "턴\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (make_pair(i, j) == EXIT) cout << "출" << " ";
            else
            cout << people[i][j] << " ";
        }
        cout << "\n";
    }
    cout << walk << "\n";
}

void Move()
{
    // next 배열 초기화
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            next_people[i][j] = 0;
        }

    // 각 칸의 사람 수가 0보다 크면 4방향 검사
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (people[i][j] > 0)
            {
                int ex = EXIT.first; int ey = EXIT.second;
                int min_dist = abs(ex - i) + abs(ey - j);
                int min_x = i; int min_y = j;
                for (int d = 0; d < 4; d++)
                {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (inRange(nx, ny) && maze[nx][ny] == 0)
                    {
                        int dist = abs(ex - nx) + abs(ey - ny);
                        if (min_dist > dist)
                        {
                            min_dist = dist;
                            min_x = nx; min_y = ny;
                        }
                    }
                }
                if (!(min_x == i && min_y == j)) walk += people[i][j];
                next_people[min_x][min_y] += people[i][j];
            }
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            people[i][j] = next_people[i][j];
            if (make_pair(i, j) == EXIT) people[i][j] = 0;
        }
    //PP();
}

void Rotate()
{
    for (int i = SX; i < SX + square_size; i++)
        for (int j = SY; j < SY + square_size; j++)
        {
            if (maze[i][j] > 0) maze[i][j]--;
            next_maze[i][j] = 0;
            next_people[i][j] = 0;
        }

    for (int i = SX; i < SX + square_size; i++)
        for (int j = SY; j < SY + square_size; j++)
        {
            int x = i - SX; int y = j - SY;
            int ox = y; int oy = square_size - x - 1;
            next_maze[ox + SX][oy + SY] = maze[i][j];
            next_people[ox + SX][oy + SY] = people[i][j];
        }
    int x = EXIT.first;
    int y = EXIT.second;
    if (SX <= x && x < SX + square_size && SY <= y && y < SY + square_size)
    {
        int ox = x - SX; int oy = y - SY;
        int rx = oy, ry = square_size - ox - 1;
        EXIT = make_pair(rx + SX, ry + SY);
    }

    
    for (int i = SX; i < SX + square_size; i++)
    {
        for (int j = SY; j < SY + square_size; j++)
        {
            maze[i][j] = next_maze[i][j];
            people[i][j] = next_people[i][j];
        }
    }
    
    //cout << "회전 후\n";
    //PP();
}

void FindMin()
{
    int ex, ey;
    tie(ex, ey) = EXIT;
    for (int sz = 2; sz < n; sz++)
        for (int x1 = 0; x1 < n - sz + 1; x1++)
            for (int y1 = 0; y1 < n - sz + 1; y1++)
            {
                int x2 = x1 + sz - 1;
                int y2 = y1 + sz - 1;
                if (!(x1 <= ex && ex <= x2 && y1 <= ey && ey <= y2)) continue;

                for (int i = x1; i <= x2; i++)
                    for (int j = y1; j <= y2; j++)
                    {
                        if (people[i][j] > 0)
                        {
                            SX = x1;
                            SY = y1;
                            square_size = sz;
                            return;
                        }
                    }
            }

}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> maze[i][j];
        }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        people[x - 1][y - 1]++;
    }
    int x, y;
    cin >> x >> y;
    EXIT = make_pair(x - 1, y - 1);

    while (k--)
    {
        // 참가자 이동
        Move();
        int p = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                p += people[i][j];
            }
        if (p == 0) break;
        // 회전
        FindMin();
        Rotate();

        //cout << EXIT.first << " " << EXIT.second << " 출구\n";
        
    }

    cout << walk << "\n";
    cout << EXIT.first + 1 << " " << EXIT.second + 1;
    return 0;
}