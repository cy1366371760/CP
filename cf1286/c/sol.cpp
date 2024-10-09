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

struct Info {
    int cnt[26];
    Info () {
        memset(cnt, 0, sizeof cnt);
    }
    Info (string s) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < s.length(); i++) {
            cnt[s[i] - 'a']++;
        }
    }
    Info (char c) {
        memset(cnt, 0, sizeof cnt);
        cnt[c - 'a']++;
    }
    bool operator ==(const Info &b) const{
        for (int i = 0; i < 26; i++) {
            if (cnt[i] != b.cnt[i]) return 0;
        }
        return 1;
    }
    bool operator <(const Info &b) const{
        for (int i = 0; i < 26; i++) {
            if (cnt[i] != b.cnt[i]) return cnt[i] < b.cnt[i];
        }
        return 0;
    }
    string to_str() {
        string res = "";
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                res += (char)('a' + i);
            }
        }
        return res;
    }
};

Info operator -(Info a, Info b) {
    Info res;
    for (int i = 0; i < 26; i++) {
        res.cnt[i] = a.cnt[i] - b.cnt[i];
        res.cnt[i] = abs(res.cnt[i]);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<char> ans(n);
    vector adj(n, vector<pair<int, string>>());
    auto ask = [&](int l, int r) {
        cout << "? " << l + 1 << ' ' << r + 1 << endl;
        int num = (r - l + 1) * (r - l + 2) / 2;
        vector res(n + 1, multiset<Info>());
        for (int i = 0; i < num; i++) {
            string s;
            cin >> s;
            int len = s.length();
            res[len].insert(Info(s));
        }
        return res;
    };
    if (n <= 3) {
        string res = "";
        for (int i = 0; i < n; i++) {
            auto nw = ask(i, i);
            auto info = (*nw[1].begin());
            res += info.to_str();
        }
        cout << "! " << res << endl;
        return;
    }
    vector<multiset<Info>> a[3];
    a[0] = ask(0, (n - 1) / 2);
    a[1] = ask(1, (n - 1) / 2);
    a[2] = ask(0, n - 1);
    string half;
    {
        string bg = "", ed = "";
        int len = (n - 1) / 2 + 1;
        for (int del = 1, l = 0, r = len - 1; l < r; del++, l++, r--) {
            Info tmp1 = *a[0][len].begin();
            int nw = len - del;
            for (int fr = 0; fr < bg.length() && fr < del; fr++) {
                tmp1 = tmp1 - Info(bg[fr]);
                if (ed.length() + fr + 1 >= del) {
                    Info tmp2 = tmp1;
                    for (int bk = 0; bk + fr + 2 <= del; bk++) {
                        tmp2 = tmp2 - Info(ed[bk]);
                    }
                    a[0][nw].extract(tmp2);
                    a[1][nw].extract(tmp2);
                }
            }
            assert(a[1][nw].size() == 1);
            Info bf = *a[0][len].begin();
            for (int i = 0; i < bg.length(); i++) {
                bf = bf - Info(bg[i]);
            }
            Info tmp = bf - (*a[1][nw].begin());
            bg += tmp.to_str();
            bool skip = 0;
            Info bk = *a[0][len].begin();
            for (int i = 0; i < ed.length(); i++) {
                bk = bk - Info(ed[i]);
            }
            // cerr << "!!" << nw << ' ' << a[0][nw].size() << nl;
            for (auto fuck : a[0][nw]) {
                if (fuck == (*a[1][nw].begin()) && !skip) {
                    skip = 1;
                    continue;
                }
                tmp = bk - fuck;
                ed += tmp.to_str();
            }
        }
        if (len & 1) {
            for (int i = 0; i < bg.length(); i++) {
                a[0][1].extract(Info(bg[i]));
            }
            for (int i = 0; i < ed.length(); i++) {
                a[0][1].extract(Info(ed[i]));
            }
            assert(a[0][1].size() == 1);
            auto las = (*a[0][1].begin());
            bg += las.to_str();
        }
        reverse(all(ed));
        half = bg + ed;
        // cerr << bg << nl;
        // cerr << ed << nl;
        // cerr << half << nl;
    }
    {
        string bg = half, ed = "";
        int len = n;
        for (int del = 1, l = 0, r = len - 1; l < r; del++, l++, r--) {
            // cerr << "????" << del << ' ' <<l << ' ' << r << ' ' << ed << nl;
            Info tmp1 = *a[2][len].begin();
            int nw = len - del;
            for (int fr = 0; fr < bg.length() && fr < del - 1; fr++) {
                tmp1 = tmp1 - Info(bg[fr]);
                if (ed.length() + fr + 1 >= del) {
                    Info tmp2 = tmp1;
                    for (int bk = 0; bk + fr + 2 <= del; bk++) {
                        tmp2 = tmp2 - Info(ed[bk]);
                    }
                    a[2][nw].extract(tmp2);
                }
            }
            assert(a[2][nw].size() == 2);
            Info bf = (*a[2][len].begin());
            for (int i = 0; i < del; i++) {
                bf = bf - Info(bg[i]);
            }
            a[2][nw].extract(bf);
            assert(a[2][nw].size() == 1);
            Info bk = *a[2][len].begin();
            for (int i = 0; i < ed.length(); i++) {
                bk = bk - Info(ed[i]);
            }
            auto fuck = *a[2][nw].begin();
            auto tmp = bk - fuck;
            ed += tmp.to_str();
        }
        reverse(all(ed));
        cout << "! " << bg << ed << endl;
    }
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}


/*

[2, n - 3]
n - 4

5

aaaabbbb
*/