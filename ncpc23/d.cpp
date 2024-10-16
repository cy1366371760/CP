#include <bits/stdc++.h>
#define nl '\n'
using namespace std;

typedef vector<int> vi;
typedef long long ll;

using ld = long double;

vector<vi> dice(3, vi(6, 0));


inline bool win(int x, int y) {
    ll wc = 0, lc = 0;

    for (int i=0;i<6;i++) {
        for (int j=0;j<6;j++) {
            wc += dice[x][i] > dice[y][j];
            lc += dice[x][i] < dice[y][j];
        }
    }

    if (wc > 0) return wc >= lc;
    return 0;
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i=0;i<3;i++) for (int j=0;j<6;j++) cin >> dice[i][j];

    ll ans = -1;
    for (int x=0;x<3;x++) {
        ll ok=1;
        for(int y=0;y<3;y++) if (x != y && !win(x, y)) ok = 0;
        if(ok) {
            ans = x;
            break;
        }
    }

    if (ans == -1) {
        cout << "No dice\n";
    }
    else {
        cout << ans+1 << nl;

    }

    return 0;
}