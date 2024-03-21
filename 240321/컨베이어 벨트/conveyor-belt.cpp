#include <iostream>

#define MAX_N 200
using namespace std;
int n, t;
int grid[2][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> t;
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        grid[0][i] = num;
    }
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        grid[1][i] = num;
    }

    while(t--){
        int first, sec;
        first = grid[0][n-1];
        sec = grid[1][n-1];
        for(int i=n-1; i>0; i--) {
            grid[0][i] = grid[0][i-1];
            grid[1][i] = grid[1][i-1];
        }
        grid[0][0] = sec;
        grid[1][0] = first;
    }

    for(int i=0; i<n; i++) cout << grid[0][i] << " ";
    cout << "\n";
    for(int i=0; i<n; i++) cout << grid[1][i] << " ";
    return 0;
}