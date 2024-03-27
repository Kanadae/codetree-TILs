#include <iostream>
using namespace std;
int n, t;
int map[3][201];
int temp[3];
int main() {
    cin >> n >> t;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    while (t--){
        for (int i = 0; i < 3; i++)
        {
            temp[i] = map[i][n-1];
        }
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = n-1; j > 0; j--)
            {
                swap(map[i][j],map[i][j-1]);
            }
        }

        map[0][0] = temp[2];
        map[1][0] = temp[0];
        map[2][0] = temp[1];
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}