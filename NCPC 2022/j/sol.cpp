// g++ "$file.cpp" -o "$file"; cat "$file-in.txt" | & ".\$file.exe"
// g++ $file.cpp -std=c++17 -o $file && time ./$file < $file-in.txt
// g++-12 $file.cpp -O2 -std=c++17 -o $file && time ./$file < $file-in.txt

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;

vi ans;
ll xo, yo, xt, yt;

void printpos() {
    ll x = xo;
    ll y = yo;
    for (auto &d:ans) {
        if (d == RIGHT) x++;
        if (d == LEFT) x--;
        if (d == UP) y++;
        if (d == DOWN) y--;
    }
    cout << x << " " << y << endl;
}

void move(int num, int dir) {
    for (int i=0;i<num;i++) ans.emplace_back(dir);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
    ll n;
    cin >> n;
    cin >> xo >> yo >> xt >> yt;
    ll tl=0, tr=0;
    vi l(31, 30), r(31,30);

    for (int i=0;i<n;i++) {
        ll x, y;
        cin >> x >> y;
        if (x > xt) r[y]++;
        if (x < xt) l[y]++;
    }

    for (auto rr:r) tr += rr;
    for (auto ll:l) tl += ll;

    move(31-xo, RIGHT);
    move(1, UP);
    move(40, RIGHT);
    move(1, DOWN);
    move(40, LEFT);

    move(yo, DOWN);

    // curpos: 31, 0

    move(1, DOWN);
    move(31-xt, LEFT);
    // xt, -1
    // printpos();
    move(yt, UP);
    move(yt, DOWN);
    move(31-xt, RIGHT);
    move(1, UP);

    // pos: 31, 0
    // printpos();
    for (int i=0;i<31;i++) {
        if (i == yt) {
            for (int j=31;j>xt+1;j--) ans.emplace_back(LEFT);
            for (int j=xt+1;j<31;j++) ans.emplace_back(RIGHT);
        }
        move(1, UP);
    }

    // pos: 31, 31
    for (int i=31;i>-1;i--) {
        if (i==xt) {
            for (int j=0;j<31-yt;j++) ans.emplace_back(DOWN);
            for (int j=0;j<31-yt;j++) ans.emplace_back(UP);
        }
        move(1, LEFT);
    }

    // pos: -1, 31
    // printpos();
    for (int i=31;i>-1;i--) {
        if (i==yt) {
            for (int j=0;j<xt;j++) ans.emplace_back(RIGHT);
            for (int j=0;j<xt;j++) ans.emplace_back(LEFT);
        }
        move(1, DOWN);
    }

    // pos: -1, -1
    // printpos();
    for (int i=-1;i<31;i++) {
        if (i==xt) {
            for (int j=0;j<yt;j++) ans.emplace_back(UP);
            for (int j=0;j<yt;j++) ans.emplace_back(DOWN);
        }
        move(1, RIGHT);
    }

    // pos: 31, -1
    // printpos();
    for (int num=1;num<=31-xt;num++) {
        move(1, UP);
        for (int i=0;i<31;i++) {
            move(num, LEFT);
            move(num, RIGHT);
            move(1, UP);
        }
        // pos: 31, 31
        // printpos();

        move(31-xt, LEFT);
        move(30-yt, DOWN);
        move(30-yt, UP);
        move(31-xt, RIGHT);

        // pos: 31, 31
        // printpos();
        move(32, DOWN);
        // 31, -1
        move(31-xt, LEFT);
        move(yt, UP);
        move(yt, DOWN);
        move(31-xt, RIGHT);
    }

    // pos:31, -1
    // printpos();
    move(32, LEFT);
    // pos: -1, -1
    // printpos();


    for (int num=1;num<=xt;num++) {
        move(1, UP);
        for (int i=0;i<31;i++) {
            move(num, RIGHT);
            move(num, LEFT);
            move(1, UP);
        }
        // pos: -1, 31
        // printpos();

        move(xt+1, RIGHT);
        move(30-yt, DOWN);
        move(30-yt, UP);
        move(xt+1, LEFT);

        // pos: -1, 31
        // printpos();
        move(32, DOWN);
        // -1, -1
        move(xt+1, RIGHT);
        move(yt, UP);
        move(yt, DOWN);
        move(xt+1, LEFT);
    }


    // cout << ans.size() << endl;

    for (auto &d:ans) {
        if (d == RIGHT) cout << "right\n";
        if (d == LEFT) cout << "left\n";
        if (d == UP) cout << "up\n";
        if (d == DOWN) cout << "down\n";
    }

	return 0;
}