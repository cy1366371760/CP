#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;
const ll inf = 1e18;

void solve() {
    int n;
    cin >> n;
    map<ll, vector<string>> sta;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        sta[val].pb(to_string(val));
    }
    auto hav = [&](ll val) -> int {
        if (!sta.count(val)) return 0;
        return sta[val].size();
    }; 
    auto add = [&](string s, string t) {
        if (s == "" || t == "") return s + t;
        return "(" + s + "+" + t + ")";
    };
    auto extract = [&](ll val) {
        assert(hav(val));
        auto res = sta[val].back();
        sta[val].pop_back();
        if (!sta[val].size()) {
            sta.erase(val);
        }
        return res;
    };
    while (1) {
        if (hav(1) && hav(2)) {
            auto one = extract(1);
            auto two = extract(2);
            sta[3].pb(add(one, two));
        } else if (hav(1) >= 3) {
            auto o1 = extract(1);
            auto o2 = extract(1);
            auto o3 = extract(1);
            sta[3].pb(add(o1, add(o2, o3)));
        } else if (hav(1) >= 2) {
            auto o1 = extract(1);
            auto o2 = extract(1);
            sta[2].pb(add(o1, o2));
        } else if (hav(1)) {
            auto o1 = extract(1);
            if (!sta.size()) {
                cout << o1 << nl;
                return;
            }
            ll val = (*sta.begin()).first;
            auto tmp = extract(val);
            sta[1 + val].pb(add(o1, tmp));
        } else break;
    }
    string res = "";
    for (auto [_, buk] : sta) {
        for (auto s : buk) {
            if (res == "") res += s;
            else res += "*" + s;
        }
    }
    cout << res << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}