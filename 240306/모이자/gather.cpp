#include <iostream>
#include <climits>

using namespace std;

int arr[101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    int min = INT_MAX;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int home;
    int sum = 0;
    int diff;
    for (int i = 0; i < n; i++)
    {
        home = i;
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            diff = abs(home - j);
            diff *= arr[j];
            sum += diff;
        }
        if (min > sum) min = sum;
    }
    cout << min;
    return 0;
}