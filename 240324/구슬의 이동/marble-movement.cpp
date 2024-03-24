#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

#define MAX_N 51
#define DIR_NUM 4
using namespace std;

int n, m, t, k;
vector<tuple<int, int, int>> ball[MAX_N][MAX_N]; // 각각 속도, 번호, 방향;
vector<tuple<int, int, int>> copy_ball[MAX_N][MAX_N]; 

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool compare(const tuple<int, int, int>& a, const tuple<int, int, int>& b){
    int s1, i1, dir1;
    int s2, i2, dir2;
    tie(s1, i1, dir1) = a;
    tie(s2, i2, dir2) = b;
    if(s1 == s2) return i1 > i2; // 속도가 같으면 번호가 큰 순
    return s1 > s2; // 속도가 빠른 순
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else return 3;
}

void Move(int x, int y, int z){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    auto [speed, num, dir] = ball[x][y][z];

    int s = speed;
    while(speed--){
        int new_x = x + dx[dir];
        int new_y = y + dy[dir];

        if(InRange(new_x, new_y)){
            x = x + dx[dir];
            y = y + dy[dir];
        }
        else{
            dir = (dir + 2) % 4;
            x = x + dx[dir];
            y = y + dy[dir];
        }
    }

    copy_ball[x][y].push_back(make_tuple(s, num, dir));
}

void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_ball[i][j].clear();
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!ball[i][j].empty()) {
                for(int k=0; k<(int)ball[i][j].size(); k++){
                    Move(i, j, k);
                }
            }
                
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ball[i][j] = copy_ball[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            sort(copy_ball[i][j].begin(), copy_ball[i][j].end(), compare);
            if(copy_ball[i][j].size() > k){
                copy_ball[i][j].resize(k); // k개 초과 구슬 제거
            }
            ball[i][j] = copy_ball[i][j]; // 업데이트된 구슬 정보 복사
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> t >> k;
    for(int i=1; i<=m; i++){
        int x, y, s;
        char dir;
        cin >> x >> y >> dir >> s;
        ball[x-1][y-1].push_back(make_tuple(s, i, Dir(dir)));
    }
    while(t--){
        Simulate();
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!ball[i][j].empty()) {
                for(int k=0; k<(int)ball[i][j].size(); k++){
                    ans++;
                }
            }
        }
    }
    cout << ans;
    return 0;
}