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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> hav;
    hav.pb(vector<int>{});
    vector<int> val(n + 5, 0);
    function<int(int, int)> cmp = [&](int x, int y) {
        return 0;
    };
    for (int i = 1; i <= m; i++) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        int vx = val[x], vy = val[y];
        if (s == "!") {
            int op = cmp(vx, vy);
            if (op == -1) cout << "<" << nl;
            else if (op == 0) cout << "=" << nl;
            else cout << ">" << nl;
        } else {

        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}