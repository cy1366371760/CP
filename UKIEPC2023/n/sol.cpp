#include<bits/stdc++.h>

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

void output(int x) {
    if (x >= 25) output(x / 26);
    cout << (char)('a' + x % 26);
}

void solve() {
    int n;
    cin >> n;
    vector<ld> v(n), uni_v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        s = s.substr(0, s.length() - 1);
        stringstream trans;
        trans << s;
        trans >> v[i];
    }
    uni_v = v;
    sort(all(uni_v));
    uni_v.erase(unique(all(uni_v)));
    for (int i = 0; i < n; i++) {
        int id = lower_bound(all(uni_v), v[i]) - uni_v.begin();
        output(id);
        cout << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}