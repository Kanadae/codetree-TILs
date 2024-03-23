#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<int> ladder[16];

vector<int> choice[16];
int temp[12];
int answer[12]; 
int cnt = 0;
int min_cnt = 100;
int total_idx;
int sign = 0;
bool is_correct()
{
    int level = 1;
    for (int i = 1; i <= n; i++)
    {
        int cur = i;
        while (level <= total_idx)
        {
            
            for (int j = 0; j < choice[level].size(); j++)
            {
                if (choice[level][j] == cur)
                {
                    cur++;
                    break;
                }
                else if (choice[level][j] == (cur - 1))
                {
                    cur--;
                    break;
                }
            }
            level++;
        }
        level = 1;
        temp[i] = cur;
        if (answer[i] != cur) return false;
    }
    return true;
}

void choose(int cur)
{
    if (cur == total_idx + 1)
    {
        if (is_correct())
        {
            sign = 1;
            cnt = 0;
            for (int i = 1; i <= total_idx; i++)
            {
                cnt += choice[i].size();
            }
            
            if (cnt < min_cnt) min_cnt = cnt;
        }
        return;
    }

    for (int i = 0; i < ladder[cur].size(); i++)
    {
        choice[cur].push_back(ladder[cur][i]);
        choose(cur + 1);
    }
    for (int i = 0; i < ladder[cur].size(); i++)
    {
        choice[cur].pop_back();
        choose(cur + 1);
    }
}

int main() {
    cin >> n >> m;
    int ak = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        ladder[y].push_back(x);
        if (ak < y) total_idx = y;
    }
    
    int turn = 1;
    int level = 1;
    for (int i = 1; i <= n; i++)
    {
        
        int cur = i;
        while (level <= total_idx)
        {
            
            for (int j = 0; j < ladder[level].size(); j++)
            {
                if (ladder[level][j] == cur)
                {
                    cur++;
                    break;
                }
                else if (ladder[level][j] == (cur - 1))
                {
                    cur--;
                    break;
                }
            }
            level++;
        }
        level = 1;
        answer[i] = cur;    
    }
    choose(1);
    if (sign == 0) cout << m;
    cout << cnt;
    return 0;
}