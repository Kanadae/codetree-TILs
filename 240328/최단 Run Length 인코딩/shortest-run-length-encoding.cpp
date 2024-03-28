#include <iostream>
#include <climits>
using namespace std;

string str;
int ans = INT_MAX;

int runLengthEncoding() {
    if(str.empty()) return 0; 

    int count = 1; 
    int resultLength = 0; 

    for(int i=1; i<str.length(); i++) {
        if(str[i] == str[i-1]) {
            count++;
        } else {
            resultLength += 1 + to_string(count).length();
            count = 1; 
        }
    }

    resultLength += 1 + to_string(count).length();

    return resultLength;
}


void Shift() {
    char temp = str[str.size()-1];
    for(int i=str.size()-1; i>0; i--) {
        str[i] = str[i-1];
    }
    str[0] = temp;
}

int main() {
    cin >> str;
    for(int i=0; i<str.size(); i++) {
        Shift();
        int len = runLengthEncoding();
        ans = min(ans, len);
    }
    cout << ans;
}