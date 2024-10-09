import heapq
import random
from collections import deque, defaultdict
import sys
import copy #use copy.deepcopy to copy data structure!
from functools import cmp_to_key
input = sys.stdin.readline
sys.setrecursionlimit(int(1e6))

##n = int(input())
##a = list(map(int, input().split()))

##自定义排序
##def mycmp(x, y):
##    return -1 if x > y else 1
##
##list.sort(a, key = cmp_to_key(mycmp))
##for i in range(0, len(a)):
##    if i > 0:
##        print("",end = ' ')
##    print(a[i], end = '')
##print("")

##alt3注释,alt4取消
##F1看帮助文档

##双端队列写bfs!!
##n, m, sx, sy = map(int, input().strip().split())
##
##dis = [[-1] * (m + 1) for i in range(n + 1)] ##多维数组酱紫开，深拷贝
##dis[sx][sy] = 0
##que = deque()
##
##dx = [-2, -2, -1, -1, 1, 1, 2, 2]
##dy = [-1, 1, -2, 2, -2, 2, -1, 1]
##
##que.append([sx, sy])
##
##while que:
##    x, y = que.popleft()
##    for d in range(0, 8):
##        nx, ny = x + dx[d], y + dy[d]
##        if nx < 1 or nx > n or ny < 1 or ny > m:
##            continue
##        if dis[nx][ny] == -1:
##            dis[nx][ny] = dis[x][y] + 1
##            que.append([nx, ny])
##
##for i in range(1, n + 1):
##    for j in range(1, m + 1):
##        print(dis[i][j], end = ' ')
##    print("")

##堆的用法& dijkstra最短路
##n, m, s = map(int, input().strip().split())
##adj = [[] for i in range(0, n + 5)]
##for i in range(0, m):
##    x, y, z = map(int, input().strip().split())
##    adj[x].append([y, z])
##
##dis = [(int)(1e18)] * (n + 1)
##dis[s] = 0
##pq = [[0, s]]
##heapq.heapify(pq)
##while pq:
##    d, nw = heapq.heappop(pq)
##    if d != dis[nw]:
##        continue
##    for v, w in adj[nw]:
##        if dis[v] > d + w:
##            dis[v] = d + w
##            heapq.heappush(pq, [d + w, v])
##for i in range(1, n + 1):
##    print(dis[i], end = ' ')

##从某个库调用方法好一点！码出‘heapq.’后，按tab会出自动补全，good！
##线段树！！

n, m = map(int, input().strip().split())
a = list(map(int, input().split()))
list.insert(a, 0, 0)

seg1 = [0] * (4 * n + 5)
laz1 = [0] * (4 * n + 5)
seg2 = [0] * (4 * n + 5)
laz2 = [0] * (4 * n + 5)

def ls(k:int):
    return k << 1
def rs(k:int):
    return k << 1 | 1
def push_up(seg, k:int):
    seg[k] = seg[ls(k)] + seg[rs(k)]
def push_down(seg, laz, l, r, k:int):
    if laz[k]:
        mid = (l + r) >> 1
        seg[ls(k)] += laz[k] * (mid - l + 1)
        seg[rs(k)] += laz[k] * (r - mid)
        laz[ls(k)] += laz[k]
        laz[rs(k)] += laz[k]
    laz[k] = 0
def ask(seg, laz, L, R, l = 1, r = n, k = 1):
    if l > R or r < L:
        return 0
    if L <= l and r <= R:
        return seg[k]
    push_down(seg, laz, l, r, k)
    mid = (l + r) >> 1
    return ask(seg, laz, L, R, l, mid, ls(k)) + ask(seg, laz, L, R, mid + 1, r, rs(k))
def upd(seg, laz, L, R, val, l = 1, r = n, k = 1):
    if l > R or r < L:
        return
    if L <= l and r <= R:
        seg[k] += val
        laz[k] += val
        return
    push_down(seg, laz, l, r, k)
    mid = (l + r) >> 1
    upd(seg, laz, L, R, val, l, mid, ls(k))
    upd(seg, laz, L, R, val, mid + 1, r, rs(k))
    push_up(seg, k)
    return
def build(seg, laz, l = 1, r = n, k = 1):
    laz[k] = 0
    if l == r:
        seg[k]= a[l]
        return
    mid = (l + r) >> 1
    build(seg, laz, l, mid, ls(k))
    build(seg, laz, mid + 1, r, rs(k))
    push_up(seg, k)
    return


build(seg1, laz1)
##for _ in range(0, m):
##    opt = list(map(int, input().split()))
##    if opt[0] == 1:
##        upd(seg1, laz1, opt[1], opt[2], opt[3])
##    else:
##        print(ask(seg1, laz1, opt[1], opt[1]))
build(seg2, laz2)
for _ in range(0, m):
    opt = list(map(int, input().split()))
    if opt[0] == 1:
        upd(seg2, laz2, opt[1], opt[1], opt[2])
    else:
        print(ask(seg2, laz2, opt[1], opt[2]))
