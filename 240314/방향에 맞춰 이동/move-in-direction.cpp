#include <iostream>
using namespace std;
int main() {
    int N;
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,-1,0,1};
    char dir;
    int d;
    int dist;
    int r = 0, c = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> dir >> dist;
        if (dir == 'E') d = 0;
        else if (dir == 'S') d = 1;
        else if (dir == 'W') d = 2;
        else if (dir == 'N') d = 3;
        r += dist * dx[d];
        c += dist * dy[d];
    }
    cout << r << " " << c;
    return 0;
}