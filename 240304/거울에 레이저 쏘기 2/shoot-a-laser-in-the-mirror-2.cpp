#include <iostream>
using namespace std;
int arr[1001][1001];
int main() {
    int d;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int N, K;
    cin >> N;
    string str;
    for (int i = 0; i < N; i++){
        cin >> str;
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = str[j];
        }
    }
    cin >> K;
    
    int kn = K;
    int x, y;
    if (kn % N == 0) kn = kn / N;
    else kn = kn / N + 1;
    if (kn == 1) {
        x = 0;
        y = K - 1;
        d = 1;
    } else if (kn == 2)
    {
        x = K - N - 1;
        y = N - 1;
        d = 2;
    } else if (kn == 3)
    {
        x = N - 1;
        y = 3 * N - K;
        d = 3;
    } else if (kn == 4)
    {
        x = 4 * N - K;
        y = 0;
        d = 0;
    }

    int cnt = 0;

    while (x >= 0 && x < N && 0 <= y && y < N)
    {
        if (d == 1 || d == 3)
        {
           if (arr[x][y]=='\\')
        {
            
            d = (d + 3) % 4;
            x = x + dx[d];
            y = y + dy[d];
            cnt++;
            
        } else if (arr[x][y]=='/')
        {
            
            d = (d + 1) % 4;
            x = x + dx[d];
            y = y + dy[d];
            cnt++;
            
        } 
        } else if (d == 2 || d == 0)
        {
            if (arr[x][y]=='\\')
        {
            
            d = (d + 1) % 4;
            x = x + dx[d];
            y = y + dy[d];
            cnt++;
            
        } else if (arr[x][y]=='/')
        {
            
            d = (d + 3) % 4;
            x = x + dx[d];
            y = y + dy[d];
            cnt++;
            
        }

        }
        

    }
    cout << cnt;
    return 0;
}