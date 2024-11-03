#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;
const ll inf = 1e18;

deque<int> operator +(deque<int> a, deque<int> b) {
    int sz = max(a.size(), b.size());
    deque<int> res;
    for (int i = 0; i < sz; i++) {
        int nw = 0;
        if (i < a.size()) nw += a[i];
        if (i < b.size()) nw += b[i];
        res.pb(nw);
    }
    return res;
}

string chk(deque<int> a, deque<int> b) {
    if (a.size() < b.size()) return "<";
    if (a.size() > b.size()) return ">";
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            if (a[i] < b[i]) return "<";
            else return ">";
        }
    }
    return "=";
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector sta(n + 5, deque<int>());
    while (m--) {
        string op;
        int i, j;
        cin >> op >> i >> j;
        if (op == "!") {
            sta[j].push_front(1);
            sta[i] = sta[i] + sta[j];
            sta[j].pop_front();
        } else {
            cout << chk(sta[i], sta[j]) << nl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}