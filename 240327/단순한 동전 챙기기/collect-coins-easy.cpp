#include <iostream>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>

#define MAX_N 20
#define COIN_NUM 9

using namespace std;

int n;
int m = 3;

char grid[MAX_N][MAX_N];

vector<pair<int, int> > coin_pos;
vector<pair<int, int> > selected_pos;
    
pair<int, int> start_pos;
pair<int, int> end_pos;

int ans = INT_MAX;

int Dist(pair<int, int> a, pair<int, int> b) {
    int ax, ay;
    tie(ax, ay) = a;
    
    int bx, by;
    tie(bx, by) = b;
    
	return abs(ax - bx) + abs(ay - by);
}

int Calc() {
    int num_moves = Dist(start_pos, selected_pos[0]);
    for(int i = 0; i < m - 1; i++)
        num_moves += Dist(selected_pos[i], selected_pos[i + 1]);
    num_moves += Dist(selected_pos[m - 1], end_pos);
    
	return num_moves;
}

void FindMinMoves(int curr_idx, int cnt) {
    if(cnt == m) {
        // 선택된 모든 조합에 대해 이동 횟수를 계산합니다.
        ans = min(ans, Calc());
        return;
    }

    if(curr_idx == (int) coin_pos.size()) 
        return;

    // curr_idx index 에 있는 동전을 선택하지 않은 경우
    FindMinMoves(curr_idx + 1, cnt);
    
    // curr_idx index 에 있는 동전을 선택한 경우
    selected_pos.push_back(coin_pos[curr_idx]);
    FindMinMoves(curr_idx + 1, cnt + 1);
    selected_pos.pop_back();
}

int main() {
	cin >> n;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if(grid[i][j] == 'S')
				start_pos = make_pair(i, j);
			if(grid[i][j] == 'E')
				end_pos = make_pair(i, j);
		}
    
    // 동전을 오름차순으로 각 위치를 집어넣습니다.
    // 이후에 증가하는 순서대로 방문하기 위함입니다.
    for(int num = 1; num <= COIN_NUM; num++) 
        for(int i = 0; i < n; i++)
		    for(int j = 0; j < n; j++)
                if(grid[i][j] == num + '0')
                    coin_pos.push_back(make_pair(i, j));
    
    FindMinMoves(0, 0);
	
	if(ans == INT_MAX)
		ans = -1;
    
	cout << ans;
	return 0;
}