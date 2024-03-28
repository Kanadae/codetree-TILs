#include <iostream>
using namespace std;

int n, m;
int map[101];
int temp[101];
int sig;

int main() {
    cin >> n >> m;
    for (int i = n-1; i >= 0; i--)
    {
        cin >> map[i];
    }

    sig = 1;

    int cont;
    while (sig)
    {
        sig = 0;
        cont = 0;
        for (int i = 0; i < n - 1; i++)
        {
            cont = 0;
            for (int j = i + 1; j < n; j++)
            {
                if (map[i] == map[j])
                {
                    cont++;
                    
                } else if (cont >= m-1)
                {
                    int idx = j - 1;
                    for (int k = 0; k <= cont; k++)
                    {
                        map[idx] = 0;
                        idx--;
                    }
                    sig = 1;
                    break;
                } else break;
            }
        }
        if (cont >= m)
        {
            int idx = n - 1;
            for (int k = 0; k < cont; k++)
            {
                map[idx] = 0;
                idx--;
                sig = 1;
            }
        }

        
        int temp_idx = 0;
        int cnt = 0;
        for (int i = n-1; i >= 0; i--)
        {
            if (map[i] != 0) {
                temp[temp_idx++] = map[i];
                cnt++;
            }
        }
        
        n = cnt;
        for (int i = n-1; i >= 0; i--)
        {
            map[i] = temp[i];
            temp[i] = 0;
        }

    }

    cout << n << "\n";
    for (int i = n - 1; i >= 0; i--) cout << map[i] << "\n";


    return 0;
}