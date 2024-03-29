#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m; // m개의 병원 선택
int map[51][51];
pair<int, int> hospital[13]; // 병원 위치
pair<int, int> person[13]; // 사람 위치
vector<pair<int, int>> vec; // 병원 선택
int hos_cnt; // 병원 수
int people; // 사람 수

// (병원x - 사람 x) + (병원 y - 사람 y)
int global_sum = 10000000;

void dfs(int cur, int hos)
{

    if (hos == hos_cnt || cur == m)
    {
        if (cur != m) return;
        int t_sum = 0;
        for (int i = 0; i < people; i++)
        {
            int x = person[i].first;
            int y = person[i].second;
            int temp = 100000;
            for (int j = 0; j < m; j++)
            {
                int hx = vec[j].first;
                int hy = vec[j].second;
                int diff = abs(hx - x) + abs(hy - y);
                if (temp > diff) temp = diff;
            }
            t_sum += temp;
        }
        if (global_sum > t_sum) global_sum = t_sum;
        return;
    }

    vec.push_back(hospital[hos]);
    dfs(cur + 1, hos + 1);
    vec.pop_back();
    dfs(cur, hos + 1);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1)
            {
                person[people++] = make_pair(i, j);
            }
            if (map[i][j] == 2)
                hospital[hos_cnt++] = make_pair(i, j);
        }
    }
    dfs(0, 0);
    cout << global_sum;
    return 0;
}