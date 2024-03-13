#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    int x = 0, y = 0;
    while(N--){
        char dir;
        int dist;
        cin >> dir >> dist;
        if(dir == 'N') y += dist;
        else if(dir == 'E') x += dist;
        else if(dir == 'W') x -= dist;
        else y -= dist;
    }
    cout << x << " " << y;
    return 0;
}