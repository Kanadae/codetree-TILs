#include <iostream>
#include <vector>
using namespace std;
int n,m;
int num[20];
vector<int> vec;
int max_num = 0;
void choose(int cur_num, int cnt)
{
    if (cur_num == n)
    {
        if (cnt == m)
        {
            int a = 0;
            for (int i = 0; i <m; i++)
            {
                a ^= vec[i];
            }
            if (a > max_num) max_num = a;
        }

        return;
    }
    
    vec.push_back(num[cur_num]);
    choose(cur_num+1,cnt+1);
    vec.pop_back();
    choose(cur_num+1,cnt);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
{
    cin >> num[i];
}
choose(0, 0);
cout << max_num;
    return 0;
}