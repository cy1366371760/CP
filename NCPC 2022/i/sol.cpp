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
    int n, m;
    cin >> n >> m;
    vector linked(n + 5, map<int, bool>());
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        linked[x][y] = linked[y][x] = 1;
    }
    vector<int> prev(n + 1, 0);
    vector<int> nxt(n + 1, 0);
    auto ins_after = [&](int x, int y) -> void {
        if (nxt[x] != -1) {
            nxt[y] = nxt[x];
            prev[nxt[x]] = y;
        }
        nxt[x] = y;
        prev[y] = x;
    };
    ins_after(0, 1);
    int imp = 1;
    for (int i = 2; i <= n; i++) {
        if (imp == 1) {
            while (nxt[imp]) {
                imp = nxt[imp];
            }
        }
        int back = 0;
        // pre -> imp  i
        int pre = prev[imp];
        back |= (nxt[imp] == 0);

        // pre i-imp
        // cerr << "??" << pre << ' ' << imp << nl;
        // cerr << "!!" << who[pre] << ' ' << who[imp] << nl;
        back |= (pre == 0);
        if (pre != 0) {
            back |= (linked[pre].count(imp) == linked[imp].count(i));
        }
        if (back) {
            ins_after(imp, i);
            if (!nxt[i]) {
                if (pre && linked[pre].count(imp) != linked[imp].count(i)) {
                    imp = imp;
                } else imp = i;
            } else if (linked[imp].count(i) == linked[i].count(nxt[i])) {
                imp = nxt[i];
            } else imp = i;
        } else {
            ins_after(pre, i);
            if (linked[pre].count(i) == linked[i].count(imp)) {
                imp = pre;
            } else imp = i;
        }
        //  cerr << i << ' ' << back << ' ' << imp << nl;
    }
    int nw = 0;
    for (int i = 1; i <= n; i++) {
        nw = nxt[nw];
        cout << nw << ' ';
    }
}

/*
 1->2->3  4 5 6

*/

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}