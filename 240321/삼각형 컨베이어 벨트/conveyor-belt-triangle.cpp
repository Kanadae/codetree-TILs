#include <iostream>

#define MAX_N 200
using namespace std;
int n, t;
int grid[3][MAX_N];

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
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        grid[2][i] = num;
    }

    while(t--){
        int first, sec, third;
        first = grid[0][n-1];
        sec = grid[1][n-1];
        third = grid[2][n-1];
        for(int i=n-1; i>0; i--) {
            grid[0][i] = grid[0][i-1];
            grid[1][i] = grid[1][i-1];
            grid[2][i] = grid[2][i-1];
        }
        grid[0][0] = third;
        grid[1][0] = first;
        grid[2][0] = sec;
    }

    for(int i=0; i<n; i++) cout << grid[0][i] << " ";
    cout << "\n";
    for(int i=0; i<n; i++) cout << grid[1][i] << " ";
    cout << "\n";
    for(int i=0; i<n; i++) cout << grid[2][i] << " ";
    return 0;
}