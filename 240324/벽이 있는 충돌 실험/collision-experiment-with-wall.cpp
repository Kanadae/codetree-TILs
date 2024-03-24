#include <iostream>
#include <vector>

#define MAX_N 51
#define DIR_NUM 4
using namespace std;

int T, N, M;
char cur_dir;
int ball[MAX_N][MAX_N][4];
int copy_ball[MAX_N][MAX_N][4];
int turn;

void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int d=0; d<DIR_NUM; d++){
                ball[i][j][d] = 0;
            }
        }
    }
}
bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else return 3;
}

void Move(int x, int y, int dir){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    int new_x = x + dx[dir];
    int new_y = y + dy[dir];
    if(InRange(new_x, new_y)){
        copy_ball[new_x][new_y][dir] += 1;
    }
    else{
        dir = (dir + 2) % 4;
        copy_ball[x][y][dir] += 1;
    }
    return;
}

void Simulate(){
    while(turn--){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                for(int d=0; d<DIR_NUM; d++){
                    copy_ball[i][j][d] = 0;
                }
            }
        }

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                for(int d=0; d<DIR_NUM; d++){
                    if(ball[i][j][d] > 0) Move(i, j, d);
                }
            }
        }

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                int sum = 0;
                for(int dir=0; dir<DIR_NUM; dir++){
                    ball[i][j][dir] = copy_ball[i][j][dir];
                    sum += ball[i][j][dir];
                }
                if(sum >= 2){
                    for(int dir=0; dir<DIR_NUM; dir++){
                        ball[i][j][dir] = 0;
                    }
                }
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--){
        init();
        cin >> N >> M;
        for(int i=0; i<M; i++){
            int x, y;
            char cur_dir;
            cin >> x >> y >> cur_dir;
            ball[x-1][y-1][Dir(cur_dir)] = 1;
        }
        turn = 2 * N;
        Simulate();

        int ans = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                for(int d=0; d<DIR_NUM; d++){
                    ans += ball[i][j][d];
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}