#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;
#define Player tuple<int,int,int,int,int> // x, y, d, s, a 좌표, 방향, 재능,총
vector<int> gun[21][21];
int n, m, k; // 격자 크기, 사람 수, 턴 수
int pdx[4] = {-1,0,1,0};
int pdy[4] = {0,1,0,-1};
int score[30];
Player player[30];
int map[21][21];

void Print()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) map[i][j] = 0;
    for (int i = 0; i < m; i++)
    {
        int x,y;
        tie(x,y,ignore,ignore,ignore) = player[i];
        map[x][y] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {    for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";

        }
        cout << "\n";    
    }
    cout <<"\n";
}

bool inRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

Player getgun(Player p)
{
    int x,y,d,s,a;
    tie(x,y,d,s,a) = p;
    gun[x][y].push_back(a);
    a = 0;
    sort(gun[x][y].rbegin(), gun[x][y].rend());
    a = gun[x][y][0];
    gun[x][y].erase(gun[x][y].begin(), gun[x][y].begin()+1);
    return {x,y,d,s,a};
}

void losemove(int loser)
{
    int x,y,d,s,a;
    tie(x,y,d,s,a) = player[loser];
    int orix = x; int oriy = y;
    gun[x][y].push_back(a);
    a = 0;
    for (int i = 0; i < 4; i++)
    {
        int td = (d + i) % 4;
        int nx = x + pdx[td];
        int ny = y + pdy[td];
        if (!inRange(nx,ny)) continue;
        bool is_same = false;
        for (int j = 0; j < m; j++)
        {
            if (j == loser) continue;
            int ox, oy;
            tie(ox,oy,ignore,ignore,ignore) = player[j];
            if (ox == nx && oy == ny)
            {
                is_same = true;
                break;
            }
        }
        if (is_same) continue;
        x = nx; y = ny; d = td; break;
    }
    if (orix == x && oriy == y)
    {
        player[loser] = {x,y,d,s,a};
    }
    else 
    {
        player[loser] = {x,y,d,s,a};
        player[loser] = getgun(player[loser]);
    }
}

void winmove(int winner)
{
    player[winner] = getgun(player[winner]);
}

void fight(int p1, int p2)
{   
    //cout << p1 + 1 << " " <<p2 +1 << "대전 상대\n";
    int x1,y1,d1,s1,a1; int x2,y2,d2,s2,a2;
    tie(x1,y1,d1,s1,a1) = player[p1]; tie(x2,y2,d2,s2,a2) = player[p2];
    //cout <<   "싸움 점수 "<< s1 << " " << a1 << " " << s2 << " " << a2 <<"\n";
    int tempscore = abs((s1+a1) - (s2 + a2));
    int winner; int loser;
    if (s1+a1 > s2+a2)
    {
        winner = p1;
        loser = p2;
    } else if (s1+a1 == s2+a2)
    {
        if (s1 > s2)
        {
            winner = p1; loser = p2;
        }
        else {
            winner = p2; loser = p1;
        }
    } else
    {
        winner = p2; loser = p1;
    }
    score[winner] += tempscore;
    losemove(loser);
    winmove(winner);
}

void movePlayer()
{
    for (int i = 0; i < m; i++)
    {
        int x,y,d,s,a;
        tie(x,y,d,s,a) = player[i];
        int nx = x + pdx[d];
        int ny = y + pdy[d];
        if (!inRange(nx,ny))
        {
            if (d < 2) d+=2;
            else d-=2;
            nx = x + pdx[d];
            ny = y + pdy[d];
        }
        player[i] = {nx,ny,d,s,a};
        int signal = 0; int rival = 0;
        for (int j = 0; j < m; j++)
        {
            if (i==j) continue;
            int tx,ty;
            tie(tx,ty,ignore,ignore,ignore) = player[j];
            if (tx == nx && ty == ny)
            {
                signal = 1; rival = j; break;
            }
        }
        if (signal == 0)
        {
            player[i] = getgun(player[i]);
        }
        else
        {
            fight(i,rival);
        }
    }

}

void simulate()
{
    //1-1. 플레이어 이동
    movePlayer();
    // 한 격자에 여러 플레이어

}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tempg;
            cin >> tempg;
            if (tempg == 0) continue;
            gun[i][j].push_back(tempg);
        }
    }

    for (int i = 0; i < m; i++)
    {
        int x,y,d,s; int a = 0;
        cin >> x >> y >> d >> s;
        x--; y--;
        player[i] = make_tuple(x,y,d,s,a);
    }

    while (k--)
    {
        simulate();
        //Print();
    }

    for (int i = 0; i < m; i++)
    {
        cout << score[i] << " ";
    }

    return 0;
}