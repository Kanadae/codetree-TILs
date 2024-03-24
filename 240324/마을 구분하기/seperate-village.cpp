#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
int map[26][26];
bool visited[26][26];
int city;
vector<int> people;
int person;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    if (!map[x][y]) return false;
    return true;
}

void dfs(int x, int y)
{
    if (!visited[x][y]) {
        visited[x][y] = true;
        person++;
    }
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (Cango(new_x, new_y))
        {
            person++;
            visited[new_x][new_y] = true;
            dfs(new_x, new_y);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 0) continue;
            if (!visited[i][j])
            {
                dfs(i, j);
                city++;
                people.push_back(person);
                person = 0;
            }
        }
    }
    cout << city << "\n";
    sort(people.begin(), people.end());
    for (int i = 0; i < city; i++)
    {
        cout << people[i] << "\n";
    }
    return 0;
}