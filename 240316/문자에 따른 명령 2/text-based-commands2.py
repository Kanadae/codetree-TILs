goto = input()

dir = 0
x, y = 0, 0

# 북 , 동, 남, 서 순서
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

for o in goto:
    if o=='L':
        dir = (dir + 3)%4
    elif o=='R':
        dir = (dir+1)%4
    elif o=='F':
        x += dx[dir]
        y += dy[dir]

print(x,y)