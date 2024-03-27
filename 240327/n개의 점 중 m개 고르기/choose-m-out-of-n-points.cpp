#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;
int n,m;
int ans = INT_MAX;
vector<pair<int, int>> num;
bool visited[21];

int Calc(){
    int max_val = 0;
    for(int i=0; i<m; i++){
        for(int j=i+1; j<m; j++){
            if(visited[i] && visited[j]){
                int x1 = num[i].first;
                int y1 = num[i].second;
                int x2 = num[j].first;
                int y2 = num[j].second;
                int dist = pow(x1-x2, 2) + pow(y1-y2, 2);
                max_val = max(max_val, dist);
            }
        }
    }
    return max_val;
}

void dfs(int cur_num, int cnt){
    if(cnt == m){
        ans = min(ans, Calc());
        return;
    }

    if(cur_num == n) return;

    visited[cur_num] = true;
    dfs(cur_num+1, cnt+1);
    visited[cur_num] = false;

    dfs(cur_num+1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        num.push_back(make_pair(x, y));
    }
    dfs(0, 0);
    cout << ans;
    return 0;
}