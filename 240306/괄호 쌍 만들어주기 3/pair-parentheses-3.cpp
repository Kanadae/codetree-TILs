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
        for (int j = i + 1; j < len; j++)
        {
            if (A[j] == ')') {
                sum++;
            }
        }
    }
    cout << sum;
    return 0;
}