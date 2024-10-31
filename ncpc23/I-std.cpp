#ifdef LOCAL
#include "geodeb.h"
#endif
#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
typedef complex<int> pt;
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (ll)u.X*v.Y-(ll)u.Y*v.X;}
auto sgn(ll a) {return a==0?0:(a>0?1:-1);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return (ll)p1.X*p2.X+(ll)p1.Y*p2.Y;}
auto norm2(pt p) {return (ll)p.X*p.X+(ll)p.Y*p.Y;}
bool comp(const pt& a, const pt& b) { return a.X<b.X or (a.X==b.X and a.Y < b.Y);}
void read(pt& p) {
    int a,b; cin >> a >> b;
    p = {a,b};
}
pt at,from;
pt vec;
bool halve(pt p) {
    auto c = ccw(from,at,p);
    if(c!=0) {
        return c<0;
    }
    return in(p-at,vec)<0;
}
bool polarcomp(pt a, pt b) {
    auto ha = halve(a),hb= halve(b);
    if(ha!=hb) {
        return ha<hb;
    }
    auto c = ccw(at,a,b);
    if(c==0) {
        return norm2(a-at)<norm2(b-at);
    }
    return c>0;
}
int next(int i, int n) {
    if(i==n-1) return 0;
    return i+1;
}
int prev(int i, int n) {
    if(i==0) return n-1;
    return i-1;
}
template <class Function>
int extremeVertex(const vector<pt>& poly, Function direction) {
  int n = static_cast<int>(poly.size()), left = 0, leftSgn;
  auto vertexCmp = [&poly, direction](int i, int j) {
    return sgn(cross(direction(poly[j]), poly[j] - poly[i])); };
  auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
    return (iSgn = vertexCmp(next(i, n), i)) >= 0 && vertexCmp(i, prev(i, n)) < 0; };
  for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
    int middle = (left + right) / 2, middleSgn;
    if (isExtreme(middle, middleSgn)) return middle;
    if (leftSgn != middleSgn ? leftSgn < middleSgn
        : leftSgn == vertexCmp(left, middle)) right = middle;
    else left = middle, leftSgn = middleSgn;
  }
  return left;
}
typedef long double F;
std::mt19937 rng(69);
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // int n = 40; 
    int n;
    cin >> n; 
    // F d = 4.3e5; 
    F d;
    cin >> d;
    from = {-1,0};
    at = {0,0};
    vector<pt> pts(n);
    for(auto& i : pts) {
        // i = {rnd(-100000,100000),rnd(-100000,100000)};
        read(i);
    }
    // for(int i=0;i<2;++i) for(int j=0;j<2;++j) pts.push_back({-80000+i*4000,-90000+j*4000});
    // n+=4;
    // pts.back() = {-200000,-140000};
    #ifdef LOCAL 
    GD_INIT("intertwined.html");
    for(auto& i : pts) {
        GD_POINT(i.X,i.Y);
    }
    #endif
    auto ori = pts;
    auto bad = [&](pt v, double len){

        return norm2(v)>len*len;
    };
    auto precomp = [&]() {
        #ifdef LOCAL
        GD_LAYER();
        GD_CIRC(at.X,at.Y,d);
        #endif
        pts.erase(partition(all(pts),[&](pt i) {
            return !bad(i-at,d);
        }),pts.end());
        // sort points radially around at
        vec = at-from;
        sort(all(pts),polarcomp);
    };
    precomp();
    if(pts.empty()) {
        cout << "-1\n";
        exit(0);
    }
    if(halve(pts[0])) {
        for(auto& i : pts) i = -i;
        for(auto& i : ori) i = -i;
    }
    


    vector<pt> hull;
    vector<F> ds;
    auto calcIntermediateHull = [&](bool first) {
        hull = {at};
        ds= {d};
        for(auto p : pts) {
            if(hull.back()==p) continue;
            int hi = extremeVertex(hull, [&p](const pt& q) { return q - p; });
            if(bad(hull[hi]-p,ds[hi])) {
                // GD_LAYER();
                // GD_SEGMENT(hull[hi].X,hull[hi].Y,p.X,p.Y,"red");
                continue;
            }
            while(hull.size()>1 and ccw(hull.end()[-2],hull.back(),p) <=0) {
                hull.pop_back();
                ds.pop_back();
            }


            ds.push_back(ds.back()-sqrtl(norm2(hull.back()-p)));
            hull.push_back(p);
            #ifdef LOCAL
            {
            GD_LAYER();
            pt prv = hull.back();
            bool f=1;
            for(auto p : hull) {
                GD_POINT(p.X,p.Y,"orange");
                if(!f) {
                    
                    GD_SEGMENT(prv.X,prv.Y,p.X,p.Y);
                }
                f=0;
                prv=p;
            }
            }
            #endif
        }
        if(first) {
            while(hull.size()>1) {
                pt v = hull.back()-hull.end()[-2];
                if(v.Y<0 or halve(hull.back())) {
                    hull.pop_back();
                    ds.pop_back();
                } else break;
            }

        }
        #ifdef LOCAL
        GD_LAYER();
        pt prv = hull.back();
        bool f=1;
        for(auto p : hull) {
            GD_POINT(p.X,p.Y,"green");
            if(!f) {
                
                GD_SEGMENT(prv.X,prv.Y,p.X,p.Y);
            }
            f=0;
            prv=p;
        }
        #endif
        d = ds.back();
        at = hull.back();
        from = hull.end()[-2];
    };

    calcIntermediateHull(1);
    while(true) {
        precomp();
        if(pts.size()<=1) {
            for(int i=0;i<n;++i) if(ori[i]==at) {
                cout << i+1 << '\n';
                return 0;
            }
        }
        calcIntermediateHull(0);
        if(!bad(hull[0]-at,d)) {
            
            // made a full convex hull
            // do full iterations?
            F total=0;
            for(int i=0;i<hull.size();++i) {
                total+=sqrt( norm2(hull[i] - hull[next(i,hull.size())]));
            }
            F times = floorl(d/total);
            #ifdef LOCAL
            GD_PAUSE() << "times: " << times << '\n';
            #endif
            d-=times*total;
        }
    }
}