#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;
#define maxn 21
#define maxm 401
int n, m, k, t;
vector<int> map[21][21];
vector<int> new_map[21][21];
pair<int,int> monopoly[21][21]; // 각 땅의 남은 독점계약 턴과 독점한 플레이어
int player[maxm][4][4]; // 플레이어번호, 현재 방향, 현재 방향에 따른 우선순위
pair<int,int> cur_player[maxm]; // 각 플레이어의 위치
int pd[maxm]; // 각 플레이어의 현재 방향
bool is_live[maxm];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1}; // 위 아래 왼 오

bool onlyone()
{
    for (int i = 2; i <= m; i++)
    {
        if (is_live[i]) return false;
    }
    return true;
}

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move()
{
    for (int i = 1; i <= m; i++)
    {
        if (!is_live[i]) continue;
        int x = cur_player[i].first; int y = cur_player[i].second;
        int mx = -1, my = -1, myd = -1; // 내가 독점계약한 땅
        int d = pd[i];
        int findnew = 0;
        for (int j = 0; j < 4; j++)
        {
            int nx = x + dx[player[i][d][j]];
            int ny = y + dy[player[i][d][j]];
            //cout << "nx , ny : " << nx << " " << ny << " 방향: " << player[i][d][j] << endl;
            if (!inRange(nx,ny)) continue; 
            if(monopoly[nx][ny].first >= t && 
            monopoly[nx][ny].second != i) continue;
            if (monopoly[nx][ny].first < t)
            {
                x = nx; y = ny; d = player[i][d][j];
                findnew = 1;
                break;
            }
            else if (mx == -1 && my == -1 && monopoly[nx][ny].second == i)
            {
                mx = nx; my = ny;
                myd = player[i][d][j];
            }
        }
        if (findnew == 0 && mx != -1 && my != -1)
        {
            x = mx; y = my;
            d = myd;
        }
        new_map[x][y].push_back(i);
        cur_player[i].first = x;
        cur_player[i].second = y;
        pd[i] = d;
    }

    for (int i = 0; i < n; i++)
    {    
        for (int j = 0; j < n; j++)
        {
            map[i][j].clear();
            for (int z = 0; z < new_map[i][j].size(); z++)
            {
                map[i][j].push_back(new_map[i][j][z]);
            }    
            new_map[i][j].clear();
        }   
    }
}

void Print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j].size() << " ";
        }
        cout << "\n";
    }

    cout << "player 위치\n";
    for (int i = 1; i <= m; i++)
    {
        //cout << cur_player[i].first << " " << cur_player[i].second << "\n";
    }
}

void kill() // 독점 갱신 및 플레이어 제거
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!map[i][j].size()) continue;
            for (int z = 1; z < map[i][j].size(); z++)
            {
                is_live[map[i][j][z]] = false;
            }
            new_map[i][j].push_back(map[i][j][0]);
            map[i][j].clear();
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (new_map[i][j].size() == 0) continue;
            map[i][j].push_back(new_map[i][j][0]);
            monopoly[i][j].first = t + k;
            monopoly[i][j].second = map[i][j][0];
            new_map[i][j].clear();
        }
    }

}

void simulate()
{
    Move();
    //Print();
    kill();
    //cout << "kill 이후\n";
    //Print();
    //cout <<"\n";
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp; // 자연수면 플레이어
            if (temp > 0)
            {
                cur_player[temp]= make_pair(i,j); // 플레이어번호와 좌표
                monopoly[i][j] = make_pair(1 + k, temp); // 턴, 플레이어
                map[i][j].push_back(temp);
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> pd[i]; // 플레이어 초기 방향
        pd[i]--;
    }

    for (int i = 1; i <= 4 * m; i++)
    {
        for (int j = 0; j < 4; j++) // 현재 방향(각 방향)
        {
            for (int d = 0; d < 4; d++)
            {
                cin >> player[i][j][d];
                player[i][j][d]--;
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        is_live[i] = true;
    }

    t = 0;
    
    while (t < 100)
    {
        t++;
        simulate();
        if (!is_live[1]) break;
        else if (onlyone()) break;
    }

    if (is_live[1] && onlyone()) cout << t;
    else cout << -1;

}