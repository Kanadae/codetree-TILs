#include <iostream>
#include <vector>
using namespace std;
int n,m;
vector<int> graph[1001];
int visited[1001];
int ans = 0;
void bfs(int cnt)
{
    for (int i = 0; i < graph[cnt].size(); i++)
    {
        int cur = graph[cnt][i];
        if(!visited[cur])
        {
            ans++;
            visited[cur] = true;
            bfs(cur);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x,y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    visited[1] = true;
    bfs(1);
    cout << ans;
    return 0;
}