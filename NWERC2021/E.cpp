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

int fen[N + 10];
void add(int x) {
    for (; x <= N; x += x & -x) fen[x]++;
}
ll ask(int x) {
    ll res = 0;
    for (; x; x -= x & -x) res += fen[x];
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<pii> a, b;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        a.pb({val, i + 1});
    }
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        b.pb({val, i + 1});
    }
    // part 1
    ll need = 0;
    {
        sort(all(a));
        reverse(all(a));
        sort(all(b));
        reverse(all(b));
        auto calc = [&](vector<pii> &cur) {
            memset(fen, 0, sizeof (fen));
            vector<ll> res;
            for (int i = 0; i < n; i++) {
                auto [val, ps] = cur[i];
                ll nw = ask(ps);
                add(ps);
                res.pb(nw);
            }  
            return res;
        };
        auto cnt_a = calc(a);
        auto cnt_b = calc(b);
        ll res = 0;
        for (int i = 0; i < n; i++) {
            // cerr << i << ' ' << cnt_a[i] << ' ' << cnt_b[i] << nl;
            res += abs(cnt_a[i] - cnt_b[i]);
        }
        cout << res << nl;
        need = min(res, (ll)200000);
    }
    // part 2
    {
        set<int> remain;
        for (int i = 1; i <= n; i++) remain.insert(i);
        vector<pii> res;
        set<pii> fir, sec;
        vector<int> wt(n + 5);
        for (auto [val, ps] : a) fir.insert({val, ps}), wt[ps] = val;
        for (auto [val, ps] : b) sec.insert({val, ps});
        auto output = [&]() {
            for (auto [p, q] : res) {
                cout << p << ' ' << q << nl;
            }
            exit(0);
        };
        auto swp = [&](int &p, int q, int &pb) {
            if (wt[p] == wt[q]) {
                if (q > p) {
                    pb = (*sec.upper_bound(pii(wt[p], pb))).second;
                } else {
                    pb = (*prev(sec.lower_bound(pii(wt[p], pb)))).second;
                }
                p = q;
                return;
            }
            res.pb({p, q});
            if (res.size() == need) output();
            fir.erase(pii(wt[p], p));
            fir.erase(pii(wt[q], q));
            swap(wt[p], wt[q]);
            fir.insert(pii(wt[p], p));
            fir.insert(pii(wt[q], q));
            p = q;
            return;
        };
        while (!fir.empty()) {
            auto [_, pa] = (*fir.begin());
            auto [__, pb] = (*sec.begin());
            // cerr << "!!! " << _ << ' ' << pa << ' ' << pb << nl;
            if (pa == pb) {
                fir.erase(fir.begin()), sec.erase(sec.begin());
                remain.erase(pa);
                continue;
            }
            if (pa < pb) {
                while (pa != pb) {
                    // cerr << "GG" << pa << ' ' << pb << nl;
                    auto it = remain.upper_bound(pa);
                    int nxt = (*it);
                    swp(pa, nxt, pb);
                }
            } else {
                while (pa != pb) {
                    auto it = prev(remain.lower_bound(pa));
                    int prev = (*it);
                    swp(pa, prev, pb);
                }
            }
            fir.erase(pii(wt[pa], pa)), sec.erase(pii(wt[pa], pb));
            remain.erase(pb);
        }
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