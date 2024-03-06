#include <iostream>
using namespace std;
int main() {
    string A;
    cin >> A;
    int len = A.length();
    int ch;
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (A[i] == ')') continue;
        ch = A[i];
        for (int j = 1; j < len - 1; j++)
        {
            if (A[j] == ')') sum++;
        }
    }
    cout << sum;
    return 0;
}