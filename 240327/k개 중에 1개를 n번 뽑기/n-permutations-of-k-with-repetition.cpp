#include <iostream>
#include <vector>

using namespace std;
int k, n;
vector<int> arr;

void dfs(int cnt){
    if(n == cnt){
        for(int i=0; i<arr.size(); i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=k; i++){
        arr.push_back(i);
        dfs(cnt+1);
        arr.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> k >> n;

    dfs(0);
    return 0;
}