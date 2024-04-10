#include <iostream>
#include <queue>
using namespace std;

int n, k;
int map[3][101];
int temp_map[3][101];
int people[101]; // 각 칸 사람 여부
int temp_people[101];

bool checkSafe()
{
    int danger = 0;
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i][j] == 0) danger++;
        }
        
    }
    return danger < k;
}

void rotate()
{
    int temp[3];
    temp[0] = map[1][n]; // 5
    temp[1] = map[2][n]; // 6
    temp[2] = map[2][1]; // 10

    for (int i = n; i >= 2; i--)
    {
        temp_map[1][i] = map[1][i-1];
    }
    for (int i = 0; i <= n-1; i++)
    {

        temp_map[2][i] = map[2][i+1];
    }
    temp_map[2][n] = temp[0];
    temp_map[1][1] = temp[2];  

    for (int i = 1; i <=2 ; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            map[i][j] = temp_map[i][j];
            temp_map[i][j] = 0;
        }
    }

    for (int i = n; i >= 2; i--)
    {
        temp_people[i] = people[i-1];
    }

    for (int i = 1; i <= n; i++)
    {
        people[i] = temp_people[i];
        temp_people[i] = 0;
    }
}

void Ride()
{
    people[n] = 0;
    for (int i = n; i >= 2; i--)
    {
        if (map[1][i] == 0 || people[i] || !people[i-1]) continue;
        people[i] = people[i-1];
        map[1][i]--;
    }
    if (map[1][1] > 0 && people[1] == 0)
    {
        people[1] = 1;
        map[1][1]--;
    }

}

void Print()
{
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void simulate()
{
    // 무빙워크 회전
    rotate();
    //Print();
    // 사람 탑승
    Ride();
}

int main() {
    cin >> n >> k;
    for (int j = 1; j <= n; j++)
    {
        cin >> map[1][j];
    }

    for (int j = n; j >= 1; j--)
    {
        cin >> map[2][j];
    }

    int t = 1;
    while (true)
    {
        simulate();
        if (!checkSafe()) break;
        t++;
    }

    cout << t;
    return 0;
}