#include <iostream>
using namespace std;
int n, m, k, life; // 격자크기, 박멸년수, 제초제확산범위, 제초제수명
int map[21][21];
int temp_map[21][21];

int remover[21][21]; // 제초제 위치와 수명

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int ddx[4] = { -1,1,1,-1 };
int ddy[4] = { 1,1,-1,-1 };

int ans;
int initial;

int main() {
    cin >> n >> m >> k >> life;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    while (m--)
    {
        // 1. 나무 성장
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] <= 0) continue;
                int grow = 0;
                for (int d = 0; d < 4; d++)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if (0 > x || x >= n || 0 > y || y >= n) continue;
                    if (map[x][y] <= 0) continue;
                    grow++;
                }
                map[i][j] += grow;
            }
        }
        
        // 2. 번식
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] <= 0) continue; // 나무가 아니면 continue
                int cnt = 0;
                for (int d = 0; d < 4; d++)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if (0 > x || x >= n || 0 > y || y >= n) continue;
                    if (map[x][y] == 0 && remover[x][y] == 0) cnt++;
                }
               
                if (cnt == 0) continue;
                int tree = map[i][j] / cnt;
                for (int d = 0; d < 4; d++)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if (map[x][y] != 0) continue;
                    temp_map[x][y] += tree;
                }
            }
        }

        // 2.1 번식 후 맵에 추가
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (temp_map[i][j] == 0) continue;
                map[i][j] += temp_map[i][j];
                temp_map[i][j] = 0;
            }
        }
        

        
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (remover[i][j] > 0) remover[i][j]--;
                }
            }

        initial = 1;

        // 3. 가장 많이 나무를 죽일 수 있는 곳에 제초제 뿌리기
        int r, c; // 제초제 뿌릴 위치
        int sig = 0;
        int max_kill = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 전부 0일 경우, 맨 첫 행 첫 열을 선택하기 위함
                if (map[i][j] == 0 && sig == 0 && max_kill == 0)
                {
                    sig = 1; // 첫행 첫열
                    r = i; c = j;
                    continue;
                }
                if (map[i][j] <= 0) continue;
                // 나무인 경우
                int temp_kill = map[i][j];
                sig = 1;
                for (int d = 0; d < 4; d++)
                {
                    int x = i; int y = j;
                    for (int t = 0; t < k; t++)
                    {
                        int nx = x + ddx[d];
                        int ny = y + ddy[d];
                        if (0 > nx || nx >= n || 0 > ny || ny >= n) break;
                        if (map[nx][ny] <= 0) break;
                        temp_kill += map[nx][ny];
                        
                        x = nx; y = ny;
                    }
                   
                }

                if (temp_kill > max_kill)
                {
                    max_kill = temp_kill;
                    r = i; c = j;
                }
            }
        }
        
        // 4. 제초제 뿌리기
        remover[r][c] = life;
        if (map[r][c] >= 1)
        {
            ans += map[r][c];
            map[r][c] = 0;

            for (int d = 0; d < 4; d++)
            {
                int x = r; int y = c;
                //cout << "hi " << x << " " << y;
                for (int t = 0; t < k; t++)
                {
                    int nx = x + ddx[d];
                    int ny = y + ddy[d];
                    if (0 > nx || nx >= n || 0 > ny || ny >= n) break;
                    if (map[nx][ny] <= 0)
                    {
                        remover[nx][ny] = life;
                        break;
                    }
                    // 나무가 있다면
                    ans += map[nx][ny];
                    map[nx][ny] = 0;
                    remover[nx][ny] = life;
                    x = nx; y = ny;
                }
            }
        }

        
 
    }

    cout << ans;

    return 0;
}