import  sys
input = sys.stdin.readline
n = int(input())

nums = list(map(int, input().split()))

stack = []

for num in nums:
    while stack and stack[-1] < num:
        stack.pop()
    stack.append(num)
    while len(stack) >= 2 and stack[-1] == stack[-2]:
        newnum = stack.pop() * 2
        stack.pop()
        stack.append(newnum)

print(stack[0])

