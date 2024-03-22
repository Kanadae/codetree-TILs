#include <iostream>
#include <vector>
using namespace std;
int n;
pair<int, int> line[16];
int best_cnt = 0;

vector<pair<int, int>> vec;

bool overlapped(int x1, int x2, int y1, int y2)
{
    if (x1 == y1 || x1 == y2 || x2 == y1 || x2 == y2) return true;
    if ((x1 > y1 && y2 > x1) || (y1 > x1 && x2 > y1)) return true;
    return false;
}



bool possible()
{
    for (int i = 0; i < vec.size(); i++)
    {
        int x1 = vec[i].first;
        int x2 = vec[i].second;

        for (int j = i + 1; j < vec.size(); j++)
        {
            int y1 = vec[j].first;
            int y2 = vec[j].second;
            if (overlapped(x1, x2, y1, y2)) return false;
        }
    }

    return true;
}

void select(int cur)
{
    if (cur == n)
    {
        if (possible())
        {
            if (best_cnt < vec.size())
            {
                best_cnt = vec.size();
            }
        }
        return;
    }

    vec.push_back(line[cur]);
    select(cur + 1);
    vec.pop_back();
    select(cur + 1);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        line[i] = make_pair(x, y);
    }

    select(0);

    cout << best_cnt;

    return 0;
}