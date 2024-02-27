#include <iostream>
using namespace std;
int arr[1000001];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i<n; i++)
    {
        cin >> arr[i];
    }
    int master, worker;
    cin >> master >> worker;
    long long check = 0;
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr[i] - master;
        check++;
        if (arr[i] > 0)
        {
            if (arr[i] % worker == 0)
            {
                check += arr[i] / worker;
            } else {
                check += arr[i] / worker + 1;
            }
        }
    }

    cout << check;


    return 0;
}