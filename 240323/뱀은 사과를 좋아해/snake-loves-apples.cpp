#include <iostream>
#include <vector>

#define MAX_N 101
#define DIR_NUM 4
using namespace std;

int N, M, K;
int total_time;
int apple[MAX_N][MAX_N];

vector<pair<int, int> > snake;

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int Dir(char dir){
    if(dir == 'U') return 0;
    else if(dir == 'R') return 1;
    else if(dir == 'D') return 2;
    else return 3;
}

bool IsTwisted(pair<int, int> newHead) {
    for(int i = 0; i < (int) snake.size(); i++)
        if(newHead == snake[i])                        
            return true;                                
    
    return false; 
}

bool PushFront(pair<int, int> newHead) {
    if(IsTwisted(newHead) == true)                        
        return false;                                     
    
    snake.insert(snake.begin(), newHead);                
    return true;                                         
}                                                         

bool MoveSnake(int new_x, int new_y) {
    if(apple[new_x][new_y] == 1) {                           
        apple[new_x][new_y] = 0;
        if(PushFront(make_pair(new_x, new_y)) == false)         
            return false;                                 
    }                                                     
    else {
        snake.pop_back(); 
        if(PushFront(make_pair(new_x, new_y)) == false)         
            return false;                                 
    }       
    return true;                                         
} 

bool Move(int dir, int dist){
    int dx[DIR_NUM] = {-1, 0, 1, 0}, dy[DIR_NUM] = {0, 1, 0, -1};

    while(dist--){
        total_time++;
        pair<int, int> head = snake.front();
        int new_x = head.first + dx[dir];
        int new_y = head.second + dy[dir];

        if(!InRange(new_x, new_y)) return false;

        if(!MoveSnake(new_x, new_y)) return false;
        
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    snake.push_back(make_pair(0, 0));
    for(int i=0; i<M; i++){
        int x, y;
        cin >> x >> y;
        apple[x-1][y-1] = 1;
    }

    while(K--){
        char dir;
        int dist;
        cin >> dir >> dist;
        if(!Move(Dir(dir), dist)) break;
    }
    cout << total_time;
    return 0;
}