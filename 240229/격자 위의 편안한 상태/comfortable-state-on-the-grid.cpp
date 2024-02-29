#include <iostream>
using namespace std;
int arr[101][101];
int main() {
    int N, M;
    int r, c;
    cin >> N >> M;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    int three;
    for (int i = 0; i < M; i++)
    {
        cin >> r >> c;
        arr[r][c] = 1;
        three = 0;
        for (int j = 0; j < 4; j++)
        {
            if (arr[r+dx[j]][c+dy[j]]==1)
            {
                three++;
            }
        }
        if (three == 3) cout << 1 << "\n";
        else cout << 0 << "\n";
    }
    return 0;
}