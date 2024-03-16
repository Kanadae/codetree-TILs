n = int(input())

arr = []

for i in range(n):
    arr.append(list(map(int, input().split())))

# 상하좌우
dx = [-1, 1, 0, 0]
dy = [0,0,-1,1]

def in_range(x):
    if x>=0 and x<n:
        return True
    return False

def three_ones(x, y):
    cnt=0
    for xx, yy in zip(dx, dy):
        r = x+xx
        c = y+yy
        if in_range(r) and in_range(c):
            if arr[r][c]==1:
                cnt+=1
                if cnt>=3:
                    return True

    return False

count=0
for i in range(n):
    for j in range(n):
        if three_ones(i,j):
            count+=1
print(count)