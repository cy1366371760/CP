import sys
input = sys.stdin.readline

mapping = {
    "I": 1,
    "V": 5,
    "X": 10,
    "L": 50,
    "C": 100,
    "D": 500,
    "M": 1000,
}

tc = int(input())
for _ in range(tc):
    # arr = list(map(int, input().split()))
    s = input()
    s = list(s[:len(s) - 1])
    arr = []
    ans = 0
    for c in s:
        while arr and arr[-1] < mapping[c]:
            ans -= arr.pop()
        arr.append(mapping[c])
    
    for num in arr:
        ans += num
    print(ans)



