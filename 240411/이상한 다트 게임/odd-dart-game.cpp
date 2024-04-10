#include <iostream>
using namespace std;
int n,m,q;
int map[51][51];
int temp_map[51][51];
int dx[4] = {-1,0,1,0}; // 위 오른쪽 아래 왼쪽
int dy[4] = {0,1,0,-1};

bool inRange(int x, int y)
{
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

void Print()
{
    cout << "\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << map[i][j] << " ";
        }
        cout <<"\n";
    }
}

void rotate(int x, int d, int k)
{
    if (d == 0) // 시계방향 회전
    {
        for (int t = 0; t < k; t++)
        {
            for (int i = 1; i <= n; i++)
            {
                if (i % x != 0) continue;
                int temp = map[i][m];
                for (int j = m; j >= 2; j--)
                {
                    map[i][j] = map[i][j-1];
                }
                map[i][1] = temp;
            }

        }
        
    }
    else if (d == 1) // 반시계 회전
    {
        for (int t = 0; t < k; t++)
        {
            for (int i = 1; i <= n; i++)
            {
                if (i % x != 0) continue;
                int tmp = map[i][1];
                for (int j = 1; j <= m-1; j++)
                {
                    map[i][j] = map[i][j+1];
                }
                map[i][m] = tmp;
            }
            //Print();
        }
    }

}

bool calc()
{
    int erased = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (map[i][j] == 0) continue;
            temp_map[i][j] = map[i][j];
            int cur = map[i][j];
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                int near;
                if (!inRange(nx,ny) && k == 3 && j == 1)
                {
                    near = map[i][m];
                } else if (!inRange(nx,ny) && k == 1 && j == m)
                {
                    near = map[i][1];
                } else if (!inRange(nx,ny)) continue;
                else near = map[nx][ny];
                if (map[i][j] == near)
                {
                    temp_map[i][j] = 0;
                    erased = 1;
                    break;
                }
            }
        }
    }

    if (erased)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                map[i][j] = temp_map[i][j];
                temp_map[i][j] = 0;
            }
        }
    } else
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                temp_map[i][j] = 0;
            }
        }   
    }
    

    return erased;
}

void regulaze()
{
    int sum = 0; int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (map[i][j] == 0) continue;
            sum += map[i][j];
            cnt++;
        }
    }
    if (cnt == 0) return;
    int aver = sum / cnt;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (map[i][j] == 0) continue;
            if (map[i][j] > aver) map[i][j]--;
            else if (map[i][j] < aver) map[i][j]++;
        }
    }
}


int main() {
    cin >> n >> m >> q;   
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
        }
    }
    
    for (int i = 0; i < q; i++)
    {
        int x, d, k;
        cin >> x >> d >> k;
        //Print();
        rotate(x,d,k);
        //cout << k << "번 회전 후\n";
        //Print();
        if (!calc())
        {
            //cout << "정규화\n";
            regulaze();
        }
        //cout << "계산후\n";
        //Print();
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ans += map[i][j];
        }
    }

    cout << ans;

    return 0;
}