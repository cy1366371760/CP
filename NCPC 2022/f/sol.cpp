#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;
const ll inf = 1e18;
#define pll pair<ll, ll>
#define fi first
#define sc second
const pll mo = pll(127, 137);
const pll mod = pll(1e9 + 7, 1e9 + 9);
const int N = 1e6 + 100;

pll bas[N];
pll operator *(pll a, pll b) {
    return pll(a.fi * b.fi % mod.fi, a.sc * b.sc % mod.sc);
}
pll operator +(pll a, pll b) {
    return pll((a.fi + b.fi) % mod.fi, (a.sc + b.sc) % mod.sc);
}
pll operator -(pll a, pll b) {
    return pll ((a.fi - b.fi + mod.fi) % mod.fi, (a.sc - b.sc + mod.sc) % mod.sc);
}

pll merge(pll a, pll b, int len_b) {
    return a * bas[len_b] + b;
}

struct Hash {
    vector<pll> vals;
    int len;
    Hash () {
        len = 0;
        vals.clear();
    }
    Hash (string s) {
        int len = s.length();
        vals.resize(len + 5);
        for (int i = 0; i < len; i++) {
            vals[i + 1] = vals[i] * mo + pll(s[i], s[i]);
        }
    }
    pll ask(int l, int r) {
        return vals[r] - vals[l - 1] * bas[r - l + 1];
    }
};

void solve() {
    int n;
    cin >> n;
    vector s(n + 5, vector<string>(n + 5));
    vector hsh(n + 5, vector<Hash>(n + 5));
    ll sum_len = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> s[i][j];
            if (i != j) {
                hsh[i][j] = Hash(s[i][j]);
                sum_len += s[i][j].length();
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (s[i][j].length() != s[j][i].length()) {
                cout << "NONE" << nl;
                return;
            }
        }
    }
    sum_len /= 2 * (n - 1);
    if (n == 2) {
        string u = s[1][2];
        string v = s[2][1];
        int len = u.length();
        vector<int> maybe;
        pll need = hsh[2][1].ask(1, len);
        for (int len1 = 1; len1 < len; len1++) {
            pll fir = hsh[1][2].ask(1, len1);
            pll sec = hsh[1][2].ask(len1 + 1, len);
            pll rev = merge(sec, fir, len1);
            if (rev == need) {
                maybe.pb(len1);
            }
        }
        if (maybe.empty()) {
            cout << "NONE" << nl;
            return;
        } else if (maybe.size() > 1) {
            cout << "MANY" << nl;
            return;
        } else {
            cout << "UNIQUE" << nl;
            string fir = "", sec = "";
            int len1 = maybe[0];
            for (int i = 0; i < len1; i++) fir += u[i];
            for (int i = len1; i < len; i++) sec += u[i];
            cout << fir << nl << sec << nl;
        }
        return;
    }
    vector<string> res(n + 5);
    for (int i = 1; i <= n; i++) {
        ll cur_len = 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            cur_len += s[i][j].length();
        }
        int len_i = (cur_len - sum_len);
        if (len_i % (n - 2) || len_i <= 0) {
            cout << "NONE" << nl;
            return;
        }
        len_i /= (n - 2);
        if (i < n) {
            auto &u = s[i][n];
            if (len_i > u.length()) {
                cout << "NONE" << nl;
                return;
            }
            res[i] = "";
            for (int j = 0; j < len_i; j++) {
                res[i] += u[j];
            }
        } else {
            auto &u = s[1][i];
            if (len_i > u.length()) {
                cout << "NONE" << nl;
                return;
            }
            res[i] = "";
            for (int j = (int)u.length() - len_i; j < u.length(); j++) {
                res[i] += u[j];
            }
        }
    }
    vector<Hash> hsh_res(n + 5);
    for (int i = 1; i <= n; i++) {
        hsh_res[i] = Hash(res[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            pll need = hsh[i][j].ask(1, s[i][j].length());
            pll fir = hsh_res[i].ask(1, res[i].length());
            pll sec = hsh_res[j].ask(1, res[j].length());
            pll hav = merge(fir, sec, res[j].length());
            if (need != hav) {
                cout << "NONE" << nl;
                return;
            }
        }
    }
    cout << "UNIQUE" << nl;
    for (int i = 1; i <= n; i++) {
        cout << res[i] << nl;
    }
}

signed main() {
    int n = 1e6 + 10;
    bas[0] = pll(1, 1);
    for (int i = 1; i <= n; i++) {
        bas[i] = bas[i - 1] * mo;
    }
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}