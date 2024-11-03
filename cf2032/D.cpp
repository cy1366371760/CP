#include<bits/stdc++.h>

#define nl '\n'
#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

#define pii pair<int, int>
#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

void solve() {
    auto ask = [&](int x, int y) -> int {
        cout << "? " << x << ' ' << y << endl;
        int re;
        cin >> re;
        return re;
    };
    int n;
    cin >> n;
    vector<int> fa(n, 0);
    fa[1] = 0;
    int st = n;
    for (int i = 2; i < n; i++) {
        int re = ask(i, 1);
        if (re == 0) {
            st = i;
            fa[st] = 1;
            break;
        }
    }
    int ptr = 2;
    for (int i = st + 1; i < n; i++) {
        int re = ask(ptr, i);
        if (re == 0) {
            fa[i] = ptr;
        } else {
            while (re == 1) {
                ++ptr;
                if (ptr == i - 1) break;
                re = ask(ptr, i);
            }
            fa[i] = ptr;
        }
        ++ptr;
    }
    cout << "! ";
    for (int i = 1; i < n; i++) {
        cout << fa[i] << ' ';
    }
    cout << endl;
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}