#include <iostream>

#define MAX_N 100
using namespace std;

int n, num;
int s1, s2, e1, e2;
int arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> arr[i];
        num++;
    }
    cin >> s1 >> e1;
    for(int i=s1-1; i<=e1-1; i++) {
        arr[i] = 0;
        num--;
    }
    
    int idx = s1-1;
    for(int i=e1; i<n; i++){
        if(arr[i] != 0){
            arr[idx++] = arr[i];
        }
    }
    cin >> s2 >> e2;
    for(int i=s2-1; i<=e2-1; i++) {
        arr[i] = 0;
        num--;
    }
    idx = s2-1;
    for(int i=e2; i<n; i++){
        if(arr[i] != 0){
            arr[idx++] = arr[i];
        }
    }
    cout << num << "\n";
    for(int i=0; i<num; i++){
        if(arr[i] != 0) cout << arr[i] << "\n";
    }
    return 0;
}