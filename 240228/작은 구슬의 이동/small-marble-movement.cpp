#include <iostream>
using namespace std;

int main() {
    int xd[4] = {1, 0, 0, -1};
    int yd[4] = {0, -1, 1, 0};
    int n, t;
    cin >> n >> t;
    int r, c, direction;
    char d;
    cin >> r >> c;
    cin >> d;
    if (d == 'U') direction = 2;
    else if (d == 'D') direction = 1;
    else if (d == 'R') direction = 0;
    else if (d == 'L') direction = 3;
    for (int i = 0; i < t; i++)
    {
        if (direction == 0) // right
        {
            if (c < n)
            {
                c++;
            } else {
                direction = 3 - direction;
            }

        }

        else if (direction == 3) // left
        {
            if (c > 1)
            {
                c--;
            } else {
                direction = 3 - direction;
            }

        }

        else if (direction == 2) // up
        {
            if (r > 1)
            {
                r--;
            } else {
                direction = 3 - direction;
                
            }

        }

        else if (direction == 1) // down
        {
            if (r < n)
            {
                r++;
            } else {
                direction = 3 - direction;
                
            }

        }

    }

    cout << r << " " << c;
    return 0;
}