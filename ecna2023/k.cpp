#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> str(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> str[i];
    }
    vector chked(n + 5, vector<int>(n + 5, -1));
    vector banned(n + 5, vector<bool> (25, 0));
    for (int i = 1; i <= n; i++) {
        int len_i = str[i].length();
        for (int j = i + 1; j <= n; j++) {
            int len_j = str[j].length();
            int cur = -1;
            if (len_i != len_j) {
                cur = -1;
            } else {
                int pre = 0;
                int suf = len_i - 1;
                while (pre < len_i && str[i][pre] == str[j][pre]) ++pre;
                while (suf >= 0 && str[i][suf] == str[j][suf]) --suf;
                if (pre == suf - 1) {
                    cur = pre;
                } else cur = -1;
            }
            chked[i][j] = chked[j][i] = cur;
        }
    }
    auto get_val = [&](char a, char b) -> int {
        return (a - 'a' + 1) * 30 + (b - 'a' + 1);
    };
    map<vector<int>, int> vis;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int ps = chked[i][j];
            if (ps == -1) continue;
            vector<int> cur;
            int sub1 = get_val(str[i][ps], str[i][ps + 1]);
            int sub2 = get_val(str[j][ps], str[j][ps + 1]);
            if (sub1 > sub2) swap(sub1, sub2);
            cur.pb(str[i].length());
            cur.pb(ps);
            cur.pb(sub1);
            cur.pb(sub2);
            vis[cur]++;
        }
    }
    int ans = 0;
    for (auto [_, c] : vis) {
        if (c == 1) ++ans;
    }
    // for (int i = 1; i <= n; i++) {
    //     int len_i = str[i].length();
    //     for (int j = i + 1; j <= n; j++) {
    //         int len_j = str[j].length();
    //         if (len_i != len_j) {
    //             continue;
    //         }
    //         for (int k = 0; k + 1 < len_i; k++) {
    //             if (str[i][k] == str[j][k] && str[i][k + 1] == str[j][k + 1]) {
    //                 banned[i][k] = banned[j][k] = 1;
    //             }
    //         }
    //     }
    // }
    // int ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = i + 1; j <= n; j++) {
    //         int ps = chked[i][j];
    //         if (ps != -1 && !banned[i][ps] && !banned[j][ps]) ++ ans;
    //     }
    // }
    // for (int i = 1; i <= n; i++) {
    //     int len = str[i].length();
    //     for (int ps = 0; ps + 1 < len; ps++) {
    //         int valid = 0;
    //         for (int j = 1; j <= n; j++) {
    //             if (j == i) continue;
    //             if (chked[i][j] == ps) {
    //                 ++valid;
    //             }
    //         }
    //         if (valid == 1) ++ans, cerr << i << '
    //     }
    // }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}