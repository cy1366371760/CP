#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector adj(n + 5, vector<int>());
    vector<int> ind(n + 5, 0);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        ind[y]++;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (!ind[i]) pq.push(i); 
    }
    vector<int> ans;
    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        ans.pb(x);
        for (int y : adj[x]) {
            --ind[y];
            if (!ind[y]) {
                pq.push(y);
            }
        }
    }
    if (ans.size() < n) {
        cout << "IMPOSSIBLE" << nl;
    } else {
        for (int x : ans) cout << x << ' ';
        cout << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}