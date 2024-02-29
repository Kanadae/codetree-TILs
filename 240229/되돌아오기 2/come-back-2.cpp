#include <iostream>
#include <cstring>
using namespace std;
int main() {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    int x = 0, y =0;
    int N;
    int d = 3;
    int ans = -1;
    string str;
    cin >> str;
    N =  str.length();

    for (int i = 0; i < N; i++)
    {
        if (str[i] == 'L')
        {
            d = (d + 3) % 4;
        } else if (str[i] == 'R')
        {
            d = (d + 1) % 4;
        } else if (str[i] == 'F')
        {
            x = x + dx[d];
            y = y + dy[d];
            
        }

        if (x==0 && y==0){
            ans = ++i;
            break;
        }
    }
    if (x==0 && y==0 && ans == -1) ans = N;
    cout << ans;
    return 0;
}