#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int ans;
int A[20];
bool visited[20];
vector<int> num;

int Calc(){
    int max_val = 0;

    for(int i=0; i<n; i++){
        if(visited[i])
            max_val ^= A[i];
    }
    return max_val;
}

void dfs(int cur_num, int cnt){
    if(m == cnt){
        ans = max(ans, Calc());
        return;
    }

    if(cur_num == n) return;

    visited[cur_num] = true;
    dfs(cur_num + 1, cnt+1);
    visited[cur_num] = false;
    
    dfs(cur_num + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> A[i];
    dfs(0, 0);
    cout << ans;
    return 0;
}