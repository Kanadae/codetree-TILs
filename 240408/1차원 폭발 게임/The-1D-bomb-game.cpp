#include <iostream>

#define MAX_N 101
using namespace std;

int n, m, end_of_array;
int bomb[MAX_N];

int GetEndOfExplosion(int start_idx, int cur_num){
    int end_idx = start_idx + 1;

    while(end_idx < end_of_array){
        if(bomb[end_idx] == cur_num) end_idx++;
        else break;
    }

    return end_idx - 1;
}

void FillZero(int start_idx, int end_idx){
    for(int i=start_idx; i<=end_idx; i++){
        bomb[i] = 0;
    }
}

void Bomb(){
    int temp[MAX_N];
    
    for(int i=0; i<end_of_array; i++) temp[i] = 0;

    int cur_idx = 0;

    for(int i=0; i<end_of_array; i++){
        if(bomb[i]) temp[cur_idx++] = bomb[i];
    }

    end_of_array = cur_idx;

    for(int i=0; i<end_of_array; i++) bomb[i] = temp[i];
}

bool Simulate(){
    bool did_explode = false;

    for(int cur_idx=0; cur_idx<end_of_array; cur_idx++){
        if(bomb[cur_idx] == 0) continue;

        int end_idx = GetEndOfExplosion(cur_idx, bomb[cur_idx]);

        if(end_idx - cur_idx + 1 >= m) {
            did_explode = true;
            FillZero(cur_idx, end_idx);
        }
    }

    Bomb();
    return did_explode;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> bomb[i];
    end_of_array = n;

    while(1){
        bool did_explode = Simulate();
        if(!did_explode) break;
    }

    cout << end_of_array << "\n";
    for(int i=0; i<end_of_array; i++) cout << bomb[i] << "\n";
    return 0;
}