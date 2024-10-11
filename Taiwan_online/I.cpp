#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;

void solve() {
    int n;
    cin >> n;
    --n;
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector dp(1 << n, vector<bool> (105, 0));
    vector prev(1 << n, vector<int> (105, 0));
    for (int i = 1; i <= 100; i++) {
        dp[0][i] = 1;
    }
    int lim = (1 << n) - 1;
    for (int sta = 0; sta <= lim; sta++) {
        for (int bit = 0; bit < n; bit++) {
            if (sta >> bit & 1) continue;
            int nw = b[bit];
            for (int las = 1; las <= 100; las++) {
                if (!dp[sta][las]) continue;
                if (nw % las || (nw / las > 100)) continue;
                if (dp[sta | (1 << bit)][nw / las] == 0) {
                    dp[sta | (1 << bit)][nw / las] = 1;
                    prev[sta | (1 << bit)][nw / las] = bit;
                }
            }
        }
    }
    auto output = [&](auto &&self, int sta, int val) -> void {
        if (sta) {
            int bit =  prev[sta][val];
            self(self, sta ^  (1 << bit), b[bit] / val);
        }
        cout << val << ' ';
    };
    for (int i = 1; i <= 100; i++) {
        if (dp[lim][i] == 1) {
            cout << "Yes" << nl;
            output(output, lim, i);
            cout << nl;
            return;
        }
    }
    cout << "No" << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}