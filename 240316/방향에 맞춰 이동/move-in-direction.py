n = int(input())

dx=[-1,0,0,1]
dy=[0, -1, 1, 0]
di = {'W':0, 'S':1,"N":2,"E":3}

x, y =0 ,0 # 현재 좌표

for i in range(n):
    to, k = map(str, input().split())
    k=int(k)
    x += (dx[di[to]]*k)
    y += (dy[di[to]]*k)

print(x, y)