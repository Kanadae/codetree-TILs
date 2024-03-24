#include <iostream>
#include <vector>
using namespace std;
int n,m;
vector<int> vec;

void choose(int cur_num, int cnt)
{
    if (cur_num == n + 1)
    {
        if (cnt == m)
        {
            for (int i = 0; i < m; i++)
            {
                cout << vec[i] << " ";
            }
            cout << "\n";
        }

        return;
    }

        vec.push_back(cur_num);
        choose(cur_num+1,cnt+1);
        vec.pop_back();
        choose(cur_num+1,cnt);
    
}

int main() {
    cin >> n >> m;
    choose(1,0);
    return 0;
}