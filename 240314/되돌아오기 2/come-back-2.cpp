#include <iostream>

#define DIR_NUM 4

using namespace std;

int ans;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string command;
    cin >> command;

    int x = 0, y = 0, dir = 0;
    for(int i=0; i<command.length(); i++){
        int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
        if(command[i] == 'L'){
            dir = (dir + 3) % 4;
            ans++;
        }
        else if(command[i] == 'R'){
            dir = (dir + 1) % 4;
            ans++;
        }
        else{
            x = x + dx[dir];
            y = y + dy[dir];
            ans++;
            if(x == 0 && y == 0){
                cout << ans;
                return 0;
            }
        }
    }
    cout << "-1";
    return 0;
}