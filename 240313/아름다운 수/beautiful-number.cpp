#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int ans;
vector<int> seq;

bool is_beatuiful()
{
    for (int i = 0; i < n; i += seq[i])
    {
        if (i + seq[i] - 1 >= n) return false;

        for (int j = i; j < i + seq[i]; j++)
        {
            if (seq[j] != seq[i]) return false;
        }
    }

    return true;
}

void choose(int cnt)
{
    if (cnt == n)
    {
        if (is_beatuiful()) ans++;
        return;
    }

    for (int i = 1; i <= 4; i++)
    {
        seq.push_back(i);
        choose(cnt+1);
        seq.pop_back();
    }
}

int main() {
    cin >> n;
    choose(0);
    cout << ans;
    return 0;
}