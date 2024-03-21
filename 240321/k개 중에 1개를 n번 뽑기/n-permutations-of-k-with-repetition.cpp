#include <iostream>
#include <vector>

using namespace std;

int k, n;

vector<int> nums;

void FindPermutations(int cnt){
    if(n == cnt){
        for(int i=0; i<(int) nums.size(); i++){
            cout << nums[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=k; i++){
        nums.push_back(i);
        FindPermutations(cnt + 1);
        nums.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> k >> n;
    FindPermutations(0);
    return 0;
}