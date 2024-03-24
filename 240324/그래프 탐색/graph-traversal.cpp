#include <iostream>
#include <vector>

#define MAX_N 1001
using namespace std;

int N, M;
vector<int> graph[MAX_N];
bool visited[MAX_N];
int cnt;

void DFS(int vertex){
    for(int i=0; i<graph[vertex].size(); i++){
        int cur_v = graph[vertex][i];
        if(!visited[cur_v]){
            cnt++;
            visited[cur_v] = true;
            DFS(cur_v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i=0; i<M; i++){
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    visited[1] = true;
    DFS(1);
    cout << cnt;
    return 0;
}