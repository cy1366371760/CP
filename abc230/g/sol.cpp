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

int pri[N];
int pnum = 0;
bool np[N];
int mu[N];

void init() {
    int n = 1e6;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) {
            pri[++pnum] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pnum && 1LL * i * pri[j] <= n; j++) {
            np[i * pri[j]] = 1;
            mu[i * pri[j]] = mu[i] * -1;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                break;
            }
        }
    }
}

const int Hash_mod = 2e7 + 100;
struct Hash_table {
	vector<pll> buk[Hash_mod];
	int ins(ll x, ll y) {
        x = 1LL * x * 200005 + y;
        int to = x % Hash_mod;
		for (auto &[val, c] : buk[to]) {
            if (val == x) {
                ++c;
                return c;
            }
        } 
        buk[to].eb(x, 1);
        return 1;
	}
	// int find(int x) {
	// 	int wh = x % Hash_mod;
	// 	for (int i = buk[wh].size() - 1; i >= 0; i--) {
	// 		if (buk[wh][i] == x) {
	// 			return i;
	// 		}
	// 	} 
	// 	return -1;
	// }
	// void del(int x, int i) {
	// 	int wh = x % Hash_mod;
	// 	if (i == buk[wh].size() - 1) buk[wh].pop_back();
	// 	else buk[wh].erase(buk[wh].begin() + i);
	// }
}hsh_T;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    ll tot = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        vector<int> fir, sec;
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                fir.pb(j);
                if (j * j != i) {
                    fir.pb(i / j);
                }
            }
        }
        for (int j = 1; j * j <= p[i]; j++) {
            if (p[i] % j == 0) {
                sec.pb(j);
                if (j * j != p[i]) {
                    sec.pb(p[i] / j);
                }
            }
        }
        for (int x : fir) {
            for (int y : sec) {
                ll c = hsh_T.ins(x, y);
                tot += (c - 1) * mu[x] * mu[y];
            }
        }
    }
    auto C2 = [&](ll x) {
        return x * (x - 1) / 2LL;
    };
    tot += C2(n);
    for (int d = 1; d <= n; d++) {
        tot -= 2LL * mu[d] * C2(n / d);
    }
    // for (int i = 1; i <= n; i++) {
    //     for (auto [x, y] : cnt[i]) {
    //         tot += 1LL * mu[i] * mu[x] * C2(y);
    //     }
    // }
    for (int i = 2; i <= n; i++) {
        if (p[i] > 1) ++tot;
    }
    cout << tot << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
    init();
        solve();
    return 0;
}