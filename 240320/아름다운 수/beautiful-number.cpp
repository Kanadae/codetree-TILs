#include <iostream>
#include <vector>
using namespace std;
int n;
int cnt = 0;
vector<int> vec;

bool is_beautiful()
{
    for (int i = 0; i < n; i++)
    {
        int c = vec[i];
        if ((i + c) > n) return false;
        for (int j = i; j < i + c; j++)
        {
            if (c != vec[j]) return false;
        }
        i = i + c - 1;
    }

    return true;
}

void choose(int cur)
{
    if (cur == n)
    {
        if (is_beautiful()) cnt++;
        return;
    }

    for (int i = 1; i <= 4; i++)
    {
        vec.push_back(i);
        choose(cur + 1);
        vec.pop_back();
    }
}

int main() {
    cin >> n;
    choose(0);
    cout << cnt;
    return 0;
}