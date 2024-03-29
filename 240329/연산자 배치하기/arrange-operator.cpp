#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;
int num[12];
int add;
int sub;
int mul;
int max_sum = INT_MIN;
int min_sum = INT_MAX;
vector<int> vec; // a는 0, s는 1, m은 2
void dfs(int cnt, int a, int s, int m)
{
    if (cnt == n - 1)
    {
        int temp_sum = num[0];
        int idx = 0;
        for (int i = 1; i < n; i++)
        {
            if (vec[idx] == 0)
            {
                temp_sum = temp_sum + num[i];
            }
            else if (vec[idx] == 1) temp_sum = temp_sum - num[i];
            else if (vec[idx] == 2) temp_sum = temp_sum * num[i];
            
            idx++;
        }
        
        if (max_sum < temp_sum) max_sum = temp_sum;
        if (min_sum > temp_sum) min_sum = temp_sum;
        return;
    }

    if (add > a)
    {
        vec.push_back(0);
        dfs(cnt + 1, a + 1, s, m);
        vec.pop_back();
    }
    if (sub > s)
    {
        vec.push_back(1);
        dfs(cnt + 1, a, s + 1, m);
        vec.pop_back();
    }
    if (mul > m)
    {
        vec.push_back(2);
        dfs(cnt + 1, a, s, m + 1);
        vec.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    cin >> add >> sub >> mul;
    dfs(0, 0, 0, 0);
    cout << min_sum << " ";
    cout << max_sum;
    return 0;
}