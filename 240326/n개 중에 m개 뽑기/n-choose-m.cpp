#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> arr;

void dfs(int cur_num, int cnt){
    if(cur_num == n+1){
        if(cnt == m){
            for(int i=0; i< (int)arr.size(); i++){
                cout << arr[i] << " ";
            }
            cout << "\n";
        }
        return;
    }

    arr.push_back(cur_num);
    dfs(cur_num+1, cnt+1);
    arr.pop_back();

    dfs(cur_num+1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    dfs(1, 0);
    return 0;
}