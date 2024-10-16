st = input()


def solve(st):
    s = list(reversed(st))
    # print(s)
    if s[0] == 'E':
        return -1

    for i in range(2, 46, 2):
        k = 1 << i
        found = True
        # print("DOING")
        for c in s:
            # print(k)
            if c == 'O':
                k -= 1
                if k % 3 != 0:
                    found = False
                    break
                k //= 3
                if k % 2 == 0:
                    found = False
                    break
                if k == 1:
                    found = False
                    break
            else:
                k = k * 2
        if found: 
            return k
    return -1


ans = solve(st)
if ans == -1:
    print("INVALID")
else:
    print(ans)

