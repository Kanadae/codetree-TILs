#include <iostream>

#define N 51
#define DIR_NUM 4

using namespace std;

int n, t;
int cur_r, cur_c;
char cur_dir;

bool InRange(int x, int y){
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else if(dir == 'L') return 3;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> t >> cur_r >> cur_c >> cur_dir;
    cur_dir = Dir(cur_dir);
    while(t--){
        int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
        int new_x = cur_r + dx[cur_dir];
        int new_y = cur_c + dy[cur_dir];
        if(!InRange(new_x, new_y)){
            cur_dir = (cur_dir + 2) % 4;
        }
        else{
            cur_r = new_x;
            cur_c = new_y;
        }
    }
    cout << cur_r << " " << cur_c;
    return 0;
}