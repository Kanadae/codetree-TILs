#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 21
using namespace std;

int n;
int ans;
int grid[MAX_N][MAX_N];
int bombed[MAX_N][MAX_N];
vector<pair<int, int>> b;
vector<int> bomb;

int Calc(){
    int cnt = 0;
    for(int i=0; i<bomb.size(); i++){
        int x = b[i].first;
        int y = b[i].second;
        bombed[x][y] = 1;
        if(bomb[i] == 0){
            if(x-2 >= 0) bombed[x-2][y] = 1; 
            if(x-1 >= 0) bombed[x-1][y] = 1; 
            if(x+1 < n) bombed[x+1][y] = 1;
            if(x+2 < n) bombed[x+2][y] = 1; 
        }
        else if(bomb[i] == 1){
            if(x-1 >= 0) bombed[x-1][y] = 1; 
            if(y-1 >= 0) bombed[x][y-1] = 1; 
            if(x+1 < n) bombed[x][y+1] = 1;
            if(y+1 < n) bombed[x+1][y] = 1; 
        }
        else if(bomb[i] == 2){
            if(x-1 >= 0 && y-1 >= 0) bombed[x-1][y-1] = 1;
            if(y+1 < n && x+1 < n) bombed[x+1][y+1] = 1;
            if(x+1 < n && y-1 >= 0) bombed[x+1][y-1] = 1;
            if(x-1>=0 && y+1 < n) bombed[x-1][y+1] = 1; 
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(bombed[i][j]) {
                cnt++;
                bombed[i][j] = 0;
            }
        }
    }
    return cnt;
}

void dfs(int cnt){
    if(cnt == (int)b.size()){
        ans = max(ans, Calc());
        return;
    }

    for(int i=0; i<=2; i++){
        bomb.push_back(i);
        dfs(cnt+1);
        bomb.pop_back();
    }
}

int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j]) b.push_back(make_pair(i, j));
        }
    }
    dfs(0);
    cout << ans;
    return 0;
}