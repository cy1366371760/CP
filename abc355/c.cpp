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

        void solve() {
            int n, t;
            cin >> n >> t;
            vector<int> a(t);
            for (int i = 0; i < t; i++) {
                cin >> a[i];
            }
            vector<int> row(n + 5, 0);
            vector<int> col(n + 5, 0);
            vector<int> diag(2, 0);
            for (int i = 0; i < t; i++) {
                int v = a[i];
                int r, c;
                --v;
                r = v / n;
                c = v % n;
                row[r]++;
                col[c]++;
                if (r == c) diag[0]++;
                if (r + c == n - 1) diag[1]++;
                if (row[r] == n || col[c] == n || diag[0] == n || diag[1] == n) {
                    cout << i + 1 << '\n';
                    return;
                }
            }
            cout << -1 << '\n';
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
