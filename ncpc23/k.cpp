#include <bits/stdc++.h>
#define pb push_back
#define nl '\n'
#define pii pair<int, int>
#define x first
#define y second
#define all(u) (u).begin(),(u).end()
using namespace std;

typedef long long ll;

using ld = long double;

inline bool test(ll num) {
    ll ans;
    cout << "buf[" << num << "]" << endl;
    cin >> ans;
    return ans != 0;
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll lo = 2, hi = 2, cur = 2;

    while (true) {
        if (test(cur)) {
            lo = cur + 1;
            cur *= 2;
        }
        else {
            hi = cur;
            break;
        }
    }

    while (lo < hi) {
        ll mi = (lo + hi) / 2ll;
        if (test(mi)) lo = mi + 1ll;
        else hi = mi;
    }

    cout << "strlen(buf) = " << lo << endl;

    return 0;
}