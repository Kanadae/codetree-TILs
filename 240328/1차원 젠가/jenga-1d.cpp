#include <iostream>
using namespace std;

int n;
int map[101];
int temp[101];
int cnt = 0 ,idx = 0;
int main() {
    cin >> n;
    for (int i = n-1; i >= 0; i--)
    {
        cin >> map[i];
    }
    cnt = n;
    for (int i = 0; i < 2; i++)
    {
        int s,e;
        cin >> s >> e;

        for (int j = cnt - e; j <= cnt - s; j++)
        {
            //cout << "j :" << j << endl;
            map[j] = 0;
        }

        for (int i = 0; i < cnt; i++)
        {
            if (map[i]!=0)
            {
                temp[idx++] = map[i];
            }
        }
        cnt = idx;
        idx = 0;
        //cout << "cnt" << cnt << endl;
        for (int i = 0; i < n; i++)
        {
            map[i] = 0;
        }
        for (int j = 0; j < cnt; j++)
        {
            map[j] = temp[j];
        }
    }

    cout << cnt << "\n";
    for (int i = cnt-1; i >= 0; i--)
    {
        cout << map[i] << "\n";
    }
    
}