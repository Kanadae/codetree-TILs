#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n = 3;
int m = 3;
int r,c,k;
int map[201][201];
vector<pair<int,int>> vec; // 빈도 수 , 해당 숫자
int num[101];

void Print()
{
    for (int i = 1; i <= n; i++)
    {   for (int j = 1; j <=m; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void nplay() // maxm 반환해야함
{
    int maxm = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            num[map[i][j]]++;
        }

        for (int j = 1; j <= 100; j++)
        {
            if (num[j] > 0) vec.push_back(make_pair(num[j],j));
        }
        for (int j = 1; j <= m; j++)
        {
            map[i][j] = 0;
        }

        sort(vec.begin(),vec.end());
        int vec_idx = 0;
        for (int j = 1; j <= vec.size()*2 - 1; j += 2)
        {
            map[i][j] = vec[vec_idx].second;
            map[i][j+1] = vec[vec_idx].first;
            vec_idx++;
        }
        if (maxm < vec.size() * 2)
        {
            maxm = vec.size() * 2;
        }
        for (int j = 1; j <= 100; j++)
        {
            num[j] = 0;
        }
        vec.clear();
    }

    m = maxm;
}

void mplay()
{
    int maxn = 0;
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            num[map[i][j]]++;
        }

        for (int i = 1; i <= 100; i++)
        {
            if (num[i] > 0) vec.push_back(make_pair(num[i],i));
        }
        for (int i = 1; i <= n; i++)
        {
            map[i][j] = 0;
        }
        sort(vec.begin(),vec.end());
        int vec_idx = 0;
        for (int i = 1; i <= vec.size()*2 - 1; i+=2)
        {
            map[i][j] = vec[vec_idx].second;
            map[i+1][j] = vec[vec_idx].first;
            vec_idx++;
        }

        if (maxn < vec.size() * 2)
        {
            maxn = vec.size() * 2;
        }
        for (int i = 1; i <= 100; i++)
        {
            num[i] = 0;
        }
        vec.clear();
    }

    n = maxn;
}

void simulate()
{
    if (n >= m)
    {
        nplay();
    }
    else
    {
        mplay();
    }

    if (n > 100) n = 100;
    if (m > 100) m = 100;
}

int main()
{
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            cin >> map[i][j];
    int t = 0;
    
    while (t < 100)
    {
        if (map[r][c] == k) break;
        t++;
        simulate();
        //cout << t << "초\n";
        //Print();
    }

    if (map[r][c] == k) cout << t;
    else cout << -1;
}