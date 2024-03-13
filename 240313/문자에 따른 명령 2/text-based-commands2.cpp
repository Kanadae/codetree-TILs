#include <iostream>

#define DIR_NUM 4

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int dir = 0, x = 0, y = 0;
    string command;
    cin >> command;
    int N = command.length();
    for(int i=0; i<N; i++){
        int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
        if(command[i] == 'L'){
            dir = (dir + 3) % 4;
        }
        else if(command[i] == 'R'){
            dir = (dir + 1) % 4;
        }
        else{
            x += dy[dir], y += dx[dir];
        }
    }
    cout << x << " " << y;
    return 0;
}