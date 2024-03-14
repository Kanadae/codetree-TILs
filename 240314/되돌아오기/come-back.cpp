#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int N;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    int x = 0, y = 0;
    int ans = 0;
    int dx[DIR_NUM] = {1, 0, -1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};
    for(int i=0; i<N; i++){
        char dir;
        int dist;
        cin >> dir >> dist;
        if(dir == 'N'){
            while(dist--){
                x = x + dx[0];
                y = y + dy[0];
                ans++;
                if(x == 0 && y == 0){
                    cout << ans;
                    return 0;
                }
            }
        }
        else if(dir == 'E'){
            while(dist--){
                x = x + dx[1];
                y = y + dy[1];
                ans++;
                if(x == 0 && y == 0){
                    cout << ans;
                    return 0;
                }
            }
        }
        else if(dir == 'S'){
            while(dist--){
                x = x + dx[2];
                y = y + dy[2];
                ans++;
                if(x == 0 && y == 0){
                    cout << ans;
                    return 0;
                }   
            }
        }
        else if(dir == 'W'){
            while(dist--){
                x = x + dx[3];
                y = y + dy[3];
                ans++;
                if(x == 0 && y == 0){
                    cout << ans;
                    return 0;
                }
            }
        }
    }
    cout << "-1";
    return 0;
}