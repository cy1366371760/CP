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
    int n = 30;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 3;
    }
    int bias = 0;
    auto output = [&](auto cur) {
        for (int j = 0; j < bias; j++) cerr << ' ';
        for (int x : cur) cerr << x << " ";
        cerr << nl;
        ++bias;
        return;
    };
    output(a);
    auto mex = [&](int x, int y) {
        vector<bool> vis(3, 0);
        vis[x] = 1;
        vis[y] = 1;
        for (int i = 0; i < 3; i++) {
            if (!vis[i]) return i;
        }
    };
    while (a.size() > 1) {
        vector<int> b;
        for (int i = 0; i < a.size() - 1; i++) {
            b.pb(mex(a[i], a[i + 1]));
        }
        swap(a, b);
        output(a);
    }
}

signed main() {
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}