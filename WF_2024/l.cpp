#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define nl '\n'
#define all(x) (x).begin(),(x).end()
using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};

void solve() {
    cerr << -20 % 20 << nl;
    int n, m;
    cin >> n >> m;
    vector blk(n + 5, vector<int>(m + 5, 1));
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++) {
            blk[i][j] = (s[j - 1] == '#' ? 1 : 0);
        }
    }
    vector<vector<pii>> maybe;
    vector<pii> bg;
    {
        vector vis(n + 5, vector(m + 5, 0));
        vector<pii> cur;
        int bx, by;
        auto dfs = [&](auto &&self, int x, int y) -> void {
            vis[x][y] = 1;
            cur.pb({x - bx, y - by});
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (!vis[nx][ny] && !blk[nx][ny]) {
                    self(self, nx, ny);
                }
            }
        };
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!vis[i][j] && !blk[i][j]) {
                    cur.clear();
                    bx = i, by = j;
                    dfs(dfs, i, j);
                    sort(all(cur));
                    maybe.pb(cur);
                    bg.pb({i, j});
                }
            }
        }
    }
    map<tuple<int, int, int>, bool> vis;
    vector<pii> robot;
    int d, cur_dir = 0;
    cin >> d;
    auto forward = [&]() {
        cout << "step" << endl;
        cin >> d;
    };
    auto left = [&]() {
        cout << "left" << endl;
        cin >> d;
        cur_dir = (cur_dir + 1) % 4;
    };
    auto right = [&]() {
        cout << "right" << endl;
        cin >> d;
        cur_dir = (cur_dir - 1 + 4) % 4;
    };
    auto rev = [&](int x) {
        if (x % 2 == 0) return 2 - x;
        else return 4 - x;
    };
    auto change_dir = [&](int to) -> void {
        int dis = (to - cur_dir + 4) % 4;
        if (dis == 0) return;
        if (dis == 3) {
            right();
        } else {
            while (cur_dir != to) left();
        }
        return;
    };
    map<pii, pii> prev;
    auto dfs = [&](auto &&self, int x, int y, int dir) -> void {
        robot.pb({x, y});
        // foward
        if (d)
        {
            int nx, ny;
            nx = x + dx[dir];
            ny = y + dy[dir];
            auto nstate = make_tuple(nx, ny, dir);
            if (!vis.count(nstate)) {
                vis[nstate] = 1;
                forward();
                if (!prev.count(pii(nx, ny))) {
                    prev[pii(nx, ny)] = pii(x, y);
                }
                self(self, nx, ny, dir);
                if (cur_dir != rev(dir)) {
                    change_dir(rev(dir));
                }
                forward();
                assert(cur_dir == rev(dir));
                auto nstate = make_tuple(x, y, cur_dir);
                if (!vis.count(nstate)) {
                    vis[nstate] = 1;
                    self(self, x, y, cur_dir);
                }
            }
        }
        for (int ndir = 0; ndir < 4; ndir++) {
            auto nstate = make_tuple(x, y, ndir);
            if (!vis.count(nstate)) {
                vis[nstate] = 1;
                change_dir(ndir);
                self(self, x, y, ndir);
            }
        }
    };
    auto go = [&](int dx, int dy) {
        if (dx == -1) change_dir(1);
        else if (dx == 1) change_dir(3);
        else if (dy == 1) change_dir(0);
        else change_dir(2);
        forward();
    };
    auto path = [&](int x, int y) {
        pii nw = pii(x, y);
        vector<pii> res;
        while (1) {
            res.pb(nw);
            if (nw == pii(0, 0)) {
                break;
            }
            nw = prev[nw];
        }
        reverse(all(res));
        for (int i = 0; i + 1 < res.size(); i++) {
            go(res[i + 1].fi - res[i].fi, res[i + 1].sc - res[i].sc);
        }
    };
    vis[make_tuple(0, 0, 0)] = 1;
    dfs(dfs, 0, 0, 0);
    int sx = 0, sy = 0;
    for (auto [x, y] : robot) sx += x, sy += y;
    // cerr << robot.size() << nl;
    if (abs(sx) % robot.size() == 0 && abs(sy) % robot.size() == 0) {
        int tx = sx / (int)robot.size();
        int ty = sy / (int)robot.size();
        bool ocr = 0;
        for (auto [x, y] : robot) {
            if (x == tx && y == ty) ocr = 1;
        }
        if (ocr) {
            path(tx, ty);
            for (auto &[x, y] : robot) {
                x -= tx, y -= ty;
            }
        }
    }
    sort(all(robot));
    robot.erase(unique(all(robot)), robot.end());
    vector<pii> ans;
    auto rotate = [&](vector<pii> &cur) {
        for (auto &[x, y] : cur) {
            swap(x, y);
            x = -x;
        }
    };
    for (int rotate_num = 0; rotate_num < 4; rotate_num++) {
        sort(all(robot));
        int bias_x = robot[0].fi, bias_y = robot[0].sc;
        vector<pii> need;
        for (auto [x, y] : robot) {
            need.pb({x - bias_x, y - bias_y});
        }
        for (int i = 0; i < maybe.size(); i++) {
            auto may = maybe[i];
            if (may == need) {
                int mx, my;
                mx = bg[i].fi - bias_x;
                my = bg[i].sc - bias_y;
                ans.pb({mx, my});
            }
        }
        rotate(robot);
    }
    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    if (ans.size() != 1) {
        cout << "no" << endl;
    } else {
        cout << "yes" << ' ' << ans[0].fi << ' ' << ans[0].sc << endl;
    }
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    solve();
    return 0;
}