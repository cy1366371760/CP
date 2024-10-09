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


void solve() {
    vector sta(4, vector<pii>());
    map<char, int> dict;
    dict['m'] = 0, dict['p'] = 1, dict['s'] = 2, dict['z'] = 3;
    map<int, char> rdict;
    rdict[0] = 'm', rdict[1] = 'p', rdict[2] = 's', rdict[3] = 'z';
    auto ask = [&](char a, char b) {
        return pii(dict[b], a - '0');
    };
    for (int i = 0; i < 4; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j += 2) {
            sta[i].pb(ask(s[j], s[j + 1]));
        }
        sort(all(sta[i]));
    }
    string s;
    cin >> s;
    deque<char> las(s.begin(), s.end());
    int who = 0;
    bool skip = 1, rev = 0;
    auto get_card = [&](int i, bool rev) {
        if (las.empty()) {
            cout << "liu ju" << nl;
            exit(0);
        }
        pii cur;
        if (!rev) {
            cur = ask(las[0], las[1]);
            las.pop_front();
            las.pop_front();
        } else {
            cur = ask(las.end()[-2], las.end()[-1]);
            las.pop_back();
            las.pop_back();
        }
        sta[i].pb(cur);
        sort(all(sta[i]));
    };
    auto consec = [&](pii a, pii b, pii c) {
        if (a.fi != b.fi || a.fi != c.fi || b.fi != c.fi) return 0;
        if (a.fi == 3) return 0;
        if (a.sc + 1 != b.sc) return 0;
        if (b.sc + 1 != c.sc) return 0;
        return 1;
    };
    auto del = [&](vector<pii> &cur, pii val) {
        sort(all(cur));
        auto ps = lower_bound(all(cur), val);
        cur.erase(ps);
    };
    auto get_giv = [&](vector<pii> a, bool print = 0) {
        vector<pii> rem;
        for (int i = 0; i < a.size(); i++) {
            if (i + 2 < a.size()) {
                if (a[i] == a[i + 1] && a[i] == a[i + 2]) {
                    i += 2;
                    continue;
                }
            }
            rem.pb(a[i]);
        }
        swap(a, rem);
        while (1) {
            bool exist = 0;
            pii fir, sec, thd;
            for (int i = 0; i < a.size(); i++) {
                for (int j = i + 1; j < a.size(); j++) {
                    for (int k = j + 1; k < a.size(); k++) {
                        if (consec(a[i], a[j], a[k])) {
                            exist = 1;
                            fir = a[i];
                            sec = a[j];
                            thd = a[k];
                            break;
                        }
                    }
                    if (exist) break;
                }
                if (exist) break;
            }
            if (!exist) break;
            del(a, fir), del(a, sec), del(a, thd);
        }
        if (a.empty()) return pii(-1, -1);
        return a.back();
    };
    auto chk_win = [&](vector<pii> a) {
        function<bool(vector<pii>)> chk_triple_consec = [&](vector<pii> a){
            if (get_giv(a) == pii(-1, -1)) return 1;
            for (int i = 0; i + 2 < a.size(); i++) {
                if (a[i] == a[i + 1] && a[i] == a[i + 2]) {
                    auto b = a;
                    del(b, a[i]);
                    del(b, a[i]);
                    del(b, a[i]);
                    if (chk_triple_consec(b)) {
                        return 1;
                    }
                }
            }
            return 0;
        };
        for (int i = 0; i + 1 < a.size(); i++) {
            if (a[i] == a[i + 1]) {
                auto b = a;
                del(b, a[i]);
                del(b, a[i]);
                if (chk_triple_consec(b)) {
                    return 1;
                }
            }
        }
        return 0;
    };
    auto respon = [&](pii a, int i) {
        sort(all(sta[i]));
        map<pii, int> cnt;
        for (auto hav : sta[i]) cnt[hav]++;
        if (cnt[a] == 3) {
            del(sta[i], a);
            del(sta[i], a);
            del(sta[i], a);
            skip = 0;
            rev = 1;
            cout << i << ' ' << "gang" << nl;
            return 1;
        } else if (cnt[a] == 2) {
            skip = 1;
            rev = 0;
            del(sta[i], a);
            del(sta[i], a);
            cout << i << ' ' << "peng" << nl;
            return 1;
        }
        return 0;
    };
    while (1) {
        if (!skip) {
            get_card(who, rev);
        }
        if (chk_win(sta[who])) {
            cout << who << ' ' << "win!" << nl;
            break;
        }
        auto giv = get_giv(sta[who], 1);
        skip = 0;
        rev = 0;
        cout << who << ' ' << giv.sc << rdict[giv.fi] << endl;
        del(sta[who], giv);
        int nxt = (who + 1) % 4;
        for (int i = 0; i < 4; i++) {
            if (i == who) continue;
            if (respon(giv, i)) {
                nxt = i;
                break;
            }
        }
        who = nxt;
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