#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
#define pii pair<int, int>
#define x first
#define y second
#define all(u) (u).begin(),(u).end()
using namespace std;

using ld = long double;

pii operator + (pii a, pii b) {
    return pii(a.x + b.x, a.y + b.y);
}
pii operator -(pii a, pii b) {
    return pii(a.x - b.x, a.y - b.y);
}

void solve() {
    int nt, ns, rmax;
    cin >> nt >> ns >> rmax;
    vector<pii> a(nt);
    map<pii, bool> tree;
    for (int i = 0; i < nt; i++) {
        cin >> a[i].x >> a[i].y;
        tree[a[i]] = 1;
    }
    sort(all(a));
    vector<pii> b(ns);
    vector<pii> neg_b(ns);
    for (int i = 0; i < ns; i++) {
        cin >> b[i].x >> b[i].y;
        neg_b[i] = pii(-b[i].x, -b[i].y);
    }
    sort(all(b));
    sort(all(neg_b));
    auto rotate = [&](vector<pii> &cur) -> void {
        // rotate counter clock wise 90 degree
        for (auto &p : cur) {
            p = pii(-p.y, p.x);
        }
    };
    vector<pii> ans;
    for (int dir = 0; dir < 4; dir++) {
        auto tmp = neg_b[0];
        vector<pii> may;
        for (auto p : a) {
            may.pb(p + tmp);
        }
        vector<pii> res;
        for (auto robot : may) { // 5000
            vector<pii> gen;
            for (auto dt : b) {
                gen.pb(robot + dt);
            }
            int ptr = 0;
            bool gg = 0;
            for (auto p : a) {
                if (ptr < gen.size() && p == gen[ptr]) {
                    ++ptr;
                    continue;
                }
                if (abs(p.x - robot.x) + abs(p.y - robot.y) <= rmax) {
                    gg = 1;
                    break;
                }
            }
            if (ptr < gen.size()) gg = 1;
            if (!gg) {
                res.pb(robot);
            }
        }
        for (int j = 1; j <= 4 - dir; j++) {
            rotate(res);
        }
        for (auto robot : res) {
            if (tree.count(robot)) continue;
            ans.pb(robot);
        }
        rotate(a);
        sort(all(a));
    }
    if (ans.size() == 0) cout << "Impossible" << nl;
    else if (ans.size() > 1) cout << "Ambiguous" << nl;
    else cout << ans[0].x << ' ' << ans[0].y << nl;
    // cerr << "All: " << nl;
    // for (auto p : ans) cerr << p.x << ' ' << p.y << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}