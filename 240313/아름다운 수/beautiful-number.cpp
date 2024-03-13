#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int cnt = 0;
vector<int> seq;

bool is_beautiful()
{
    for (int i = 0; i < n; i += seq[i])
    {
        if (i + seq[i] - 1 >= n)
            return false;

        for (int j = i; j < i + seq[i]; j++)
        {
            if (seq[j]!=seq[i])
                return false;
        }
    }

    return true;
}

void choose(int cur_num)
{
    if (cur_num == n)
    {
        if (is_beautiful()) cnt++;
        return;
    }

    for (int i = 1; i <= 4; i++)
    {
        seq.push_back(i);
        choose(cur_num + 1);
        seq.pop_back();
    }
    


}

int main() {
    cin >> n;
    choose(0);
    cout << cnt;
    return 0;
}