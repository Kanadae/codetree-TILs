#include <iostream>
#include <vector>
using namespace std;
int K, N;
vector<int> vec;

void Print()
{
    for (int i = 0; i < N; i++)
    {
        cout << vec[i] << " ";
    }
    cout << "\n";
}

void choose(int cur)
{
    if (cur == N)
    {
        Print();
        return;
    }

    for (int i = 1; i <= K; i++)
    {
        vec.push_back(i);
        choose(cur + 1);
        vec.pop_back();
    }
}

int main() {
    cin >> K >> N;
    choose(0);
    return 0;
}