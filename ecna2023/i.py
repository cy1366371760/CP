import  sys
input = sys.stdin.readline
n = int(input())


m = {str(i):i for i in range(10)}
m['X'] = 10



def isvalid(isbn):
    if not checksum(isbn):
        return False
    numhyp = isbn.count('-')
    if (
        numhyp > 3 or
        isbn[0] == '-' or isbn[-1]=='-' or
        (numhyp == 3 and isbn[-2] != '-') or
        '--' in isbn
    ):
        return False
    return True


def checksum(isbn):
    ans = 0
    isbn = isbn.replace("-", '')
    if len(isbn) != 10:
        return False
    mul = 10
    for snum in isbn[:-1]:
        if snum == 'X':
            return False
    for num in isbn:
        ans += m[num] * mul
        mul -= 1
    return ans % 11 == 0


def newcs(isbn):
    ans = 0
    isbn = isbn.replace('-', '')[:-1]
    muls = [1, 3]
    for i, snum in enumerate(isbn):
        ans += m[snum] * muls[i%2]
    return str((-ans)%10)


for _ in range(n):
    isbn = input().strip()
    if not isvalid(isbn):
        print('invalid')
        continue
    newisbn = '978-' + isbn
    cs = newcs(newisbn)
    print(newisbn[:-1] + cs)


