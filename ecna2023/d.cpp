#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
using namespace std;

void solve() {
    int n = 5;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        sum += a * b;
    }
    sum /= n;
    int a, b;
    cin >> a >> b;
    cout << sum * a / b << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}