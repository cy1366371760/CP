#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;


set<ii> vis;
vi s, t;
ii sstate, tstate;
vector<vi> nexts, nextt;


inline ii nextstate(ii cur, int n) {
    auto [si, ti] = cur;
    int sin = nexts[si][n];
    int tin = nextt[ti][n];
    return ii(sin, tin);
}

ii findstate(vi &str) {
    int si = 0, ti = 0;
    for (auto &n:str) {
        si = nexts[si][n];
        ti = nextt[ti][n];
    }
    return ii(si, ti);
}

bool dfs(ii u, ii x) {
    if (vis.find(u) != vis.end()) return u == x;
    vis.emplace(u);
    ii n1 = nextstate(u, 0), n2 = nextstate(u, 1);
    if (n1 != u && dfs(n1, x)) return true;
    if (n2 != u && dfs(n2, x)) return true;
    return false;
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int tc; cin >> tc;
    while (tc--) {
        string a, ss, ts;
        cin >> a >> ss >> ts;
        if (a.size() > 2) {
            cout << "0\n";
            continue;
        }

        s.clear();
        t.clear();
        for (auto &c:ss) s.emplace_back(c != a[0]);
        for (auto &c:ts) t.emplace_back(c != a[0]);

        sstate = findstate(s);
        tstate = findstate(t);

        nexts.assign(500, vi(2, 0));
        nextt.assign(500, vi(2, 0));

        for (int i=0;i<s.size();i++) {
            nexts[i][s[i]] = (i+1)%s.size();
            nexts[i][!s[i]] = 0;
            for (int j=0;j<i;j++) {
                int ok = 1;
                for (int k=0;k<j;k++) if (s[k] != s[i-j+k]) ok = 0;
                if (ok) nexts[i][!s[i]] = j;
            }
        }

        for (int i=0;i<t.size();i++) {
            nextt[i][t[i]] = (i+1)%t.size();
            nextt[i][!t[i]] = 0;
            for (int j=0;j<i;j++) {
                int ok = 1;
                for (int k=0;k<j;k++) if (t[k] != t[i-j+k]) ok = 0;
                if (ok) nextt[i][!t[i]] = j;
            }
        }

        int ans = 1;
        vis.clear();
        if (dfs(sstate, sstate)) ans = 0;
        vis.clear();
        if (dfs(tstate, tstate)) ans = 0;
        cout << ans << "\n";
    }
    return 0;
}