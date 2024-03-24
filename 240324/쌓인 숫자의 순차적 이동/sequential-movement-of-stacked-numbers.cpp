#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 21
#define DIR_NUM 8
using namespace std;

int n, m;
vector<int> nums[MAX_N][MAX_N];
int temp[MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y, int target){
    int row = -1, col = -1;
    int dx[DIR_NUM] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[DIR_NUM] = {1, 0, -1, 1, -1, -1, 0, 1};
    int maxVal = 0;

    for(int i=0; i<DIR_NUM; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        for(int j=0; j<(int) nums[new_x][new_y].size(); j++){
            if(InRange(new_x, new_y) && maxVal < nums[new_x][new_y][j]){
                maxVal = max(maxVal, nums[new_x][new_y][j]);
                row = new_x, col = new_y;
            }
        }
    }
    if(row != -1) {
        while(true){
            int popSize = (int) nums[x][y].size();
            int idx = 0;
            for(int i=0; i<popSize; i++){
                int popNum = nums[x][y].back();
                temp[idx++] = popNum; 
                nums[x][y].pop_back();
                if(target == popNum){
                    for(int j=idx-1; j>=0; j--){
                        nums[row][col].push_back(temp[j]);
                    }
                    return;
                } 
            }
        }
    }
    return;
}

void Simulate(int target){
    for(int i=0; i<n; i++) temp[i] = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<(int) nums[i][j].size(); k++){
                if(nums[i][j][k] == target) {
                    Move(i, j, target);
                    return;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num;
            cin >> num;
            nums[i][j].push_back(num);
        }
    }

    for(int i=0; i<m; i++){
        int target;
        cin >> target;
        Simulate(target);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int popSize = (int) nums[i][j].size();
            if(popSize == 0) cout << "None";
            else{
                for(int k=popSize-1; k>=0; k--){
                    cout << nums[i][j][k] << " ";
                }
            }
            cout << "\n";   
        }
    }
    return 0;
}