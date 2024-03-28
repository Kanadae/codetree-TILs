#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAX_N 50
#define DIR_NUM 4
using namespace std;

int n, m, t;
vector<tuple<int, int, int>> ball[MAX_N][MAX_N]; // 무게, 번호, 방향
vector<tuple<int, int, int>> copy_ball[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else return 3; // 'L'
}

void Move(int x, int y){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    for (const auto& b : ball[x][y]) {
        int w, num, dir;
        tie(w, num, dir) = b;

        int new_x = x + dx[dir];
        int new_y = y + dy[dir];

        if(InRange(new_x, new_y)){
            copy_ball[new_x][new_y].push_back(make_tuple(w, num, dir));
        }
        else{
            dir = (dir + 2) % 4;
            copy_ball[x][y].push_back(make_tuple(w, num, dir));
        }
    }
}

void Merge(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(copy_ball[i][j].size() > 1){
                int weightSum = 0, maxNum = 0, dir = 0;
                for(auto &b : copy_ball[i][j]){
                    int w, num, d;
                    tie(w, num, d) = b;
                    weightSum += w;
                    if(maxNum < num){
                        maxNum = num;
                        dir = d;
                    }
                }
                copy_ball[i][j].clear();
                copy_ball[i][j].push_back(make_tuple(weightSum, maxNum, dir));
            }
        }
    }
}

void Simulate(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            copy_ball[i][j].clear();
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!ball[i][j].empty()) Move(i, j);
        }
    }

    Merge();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ball[i][j] = copy_ball[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> t;
    for(int i=1; i<=m; i++){
        int r, c, w;
        char d;
        cin >> r >> c >> d >> w;
        ball[r-1][c-1].push_back(make_tuple(w, i, Dir(d)));
    }

    while(t--){
        Simulate();
    }
    int max_w = 0;
    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!ball[i][j].empty()){
                for(auto &b : ball[i][j]){
                    int w;
                    tie(w, ignore, ignore) = b;
                    max_w = max(max_w, w);
                }
                cnt++;
            }
        }
    }
    cout << cnt << " " << max_w;
    return 0;
}