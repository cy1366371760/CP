#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 7;
int a[maxn];
#define EF if(ch==EOF) return x;
// #define lc k<<1
// #define rc k<<1|1
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;EF;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct tree
{
    int l , r;
    int miax , maxx;
    ll sum;
    int set_lazy;
}t[maxn << 2];


// inline void push_up(int k){
//     // sum[k]=sum[lc]+sum[rc];
//     // mx[k]=max(mx[lc],mx[rc]);
//     // se[k]=max(se[lc],se[rc]);
//     // mc[k]=0;
//     // if(mx[lc]!=mx[rc]) se[k]=max(se[k],min(mx[lc],mx[rc]));
//     // if(mx[k]==mx[lc]) mc[k]+=mc[lc];
//     // if(mx[k]==mx[rc]) mc[k]+=mc[rc];
//     t[k].sum = t[lc].sum + t[rc].sum;
//     t[k].maxx = max(t[lc].maxx,t[rc].maxx);
//     t[k].miax = max(t[lc].miax,t[rc].miax);
//     t[k].set_lazy = 0;
//     if(t[lc].maxx != t[rc].maxx) t[k].miax = max(t[k].miax,min(t[lc].maxx,t[rc].maxx));
//     if(t[k].maxx == t[lc].maxx) t[k].set_lazy += t[lc].set_lazy;
//     if(t[k].maxx == t[rc].maxx) t[k].set_lazy += t[rc].set_lazy;

// }
inline void push_up(int rt){
    t[rt].sum = t[rt << 1].sum + t[rt << 1|1].sum;
   // t[rt].minn = min(t[rt << 1].minn,t[rt << 1|1].minn);
    t[rt].maxx = max(t[rt << 1].maxx,t[rt << 1|1].maxx);
    t[rt].miax = max(t[rt << 1].miax, t[rt << 1|1].miax);
    t[rt].set_lazy = 0;
    if(t[rt << 1].maxx != t[rt <<1|1].maxx) t[rt].miax = max(t[rt].miax,min(t[rt << 1].maxx , t[rt <<1|1].maxx));
    //打上标记，记录下标记个数
    if(t[rt].maxx == t[rt << 1].maxx) t[rt].set_lazy += t[rt << 1].set_lazy;
    if(t[rt].maxx == t[rt << 1|1].maxx) t[rt].set_lazy += t[rt << 1|1].set_lazy;
   // cout << t[rt].sum << " " << rt <<endl;
}

inline void dec_tag(int rt,int v){
    if(v >= t[rt].maxx) return;
    t[rt].sum += 1ll * (v - t[rt].maxx)*t[rt].set_lazy;
    t[rt].maxx = v;
}

inline void push_down(int rt){
    dec_tag(rt << 1,t[rt].maxx);
    dec_tag(rt << 1|1,t[rt].maxx);
}
  // inline void push_down(int rt) {
  //       if(t[rt].set_lazy) { ///if set_lazy add_lazy = 0
  //           t[rt<<1].set_lazy = t[rt].set_lazy;
  //           t[rt<<1].sum = (t[rt<<1].r - t[rt<<1].l + 1) * t[rt].set_lazy;
  //           t[rt<<1].maxx = t[rt].set_lazy;
  //           t[rt<<1].minn = t[rt].set_lazy;
  //           t[rt<<1|1].set_lazy = t[rt].set_lazy;
  //           t[rt<<1|1].sum = (t[rt<<1|1].r - t[rt<<1|1].l + 1) * t[rt].set_lazy;
  //           t[rt<<1|1].maxx = t[rt].set_lazy;
  //           t[rt<<1|1].minn = t[rt].set_lazy;
  //           //tre[rt].add_lazy = 0;
  //           //tre[rt<<1].add_lazy = tre[rt<<1|1].add_lazy = 0;
  //           t[rt].set_lazy = 0;
  //           return ;
  //       }
  //       // if(tre[rt].add_lazy) {
  //       //     tre[rt<<1].add_lazy += tre[rt].add_lazy;
  //       //     tre[rt<<1].sum += (tre[rt<<1].r - tre[rt<<1].l + 1) * tre[rt].add_lazy;
  //       //     tre[rt<<1].max += tre[rt].add_lazy;
  //       //     tre[rt<<1].min += tre[rt].add_lazy;
  //       //     tre[rt<<1|1].add_lazy += tre[rt].add_lazy;
  //       //     tre[rt<<1|1].sum += (tre[rt<<1|1].r - tre[rt<<1|1].l + 1) *
  //       //                         tre[rt].add_lazy;
  //       //     tre[rt<<1|1].max += tre[rt].add_lazy;
  //       //     tre[rt<<1|1].min += tre[rt].add_lazy;
  //       //     tre[rt].add_lazy = 0;
  //       // }
  //   }

void build(int rt,int l ,int r){
    t[rt].l = l, t[rt].r = r;
    //t[rt].set_lazy = 1;

    if(l == r){
        t[rt].sum =  t[rt].maxx = a[l];
        t[rt].miax = -1;
        t[rt].set_lazy = 1;
       // cout <<"nbb  " <<t[rt].sum << " "<<rt << endl;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt <<1,l,mid);
    build(rt << 1|1,mid + 1,r);
    push_up(rt);
}

void up_date(int rt,int l,int r,int d){
    if(d >= t[rt].maxx) return;

    //push_down(rt);
    if(l <= t[rt].l && r >= t[rt].r && d > t[rt].miax){
     // t[rt].sum = (t[rt].r - t[rt].l + 1) * d;
     // t[rt].maxx = d;
     // t[rt].minn = d;
     // t[rt].set_lazy = d;
     dec_tag(rt,d);
     return;
 }
 push_down(rt);
 int mid = (t[rt].l + t[rt].r) >> 1;
 if(r <= mid) {
    up_date(rt<<1,l,r,d);
} else if(l > mid) {
    up_date(rt<<1|1,l,r,d);
} else {
    up_date(rt<<1,l,mid,d);
    up_date(rt<<1|1,mid+1,r,d);
}
push_up(rt);
}





 ll query_sum(int rt,int l,int r) { ///sum

    if(l <= t[rt].l && t[rt].r <= r) {
        return t[rt].sum;
    }
    push_down(rt);
    int mid = (t[rt].l + t[rt].r) >> 1;
    if(r <= mid) {
        return query_sum(rt<<1,l,r);
    } else if(l > mid) {
        return query_sum(rt<<1|1,l,r);
    } else {
        return query_sum(rt<<1,l,mid) + query_sum(rt<<1|1,mid+1,r);
    }
}

    int query_max(int rt,int l,int r) { ///max

       //cout << t[rt].maxx  << endl;
        if(l <= t[rt].l && t[rt].r <= r) {
            return t[rt].maxx;
        }
        push_down(rt);
        int mid = (t[rt].l + t[rt].r) >> 1;
        if(r <= mid) {
            return query_max(rt<<1,l,r);
        } else if(l > mid) {
            return query_max(rt<<1|1,l,r);
        } else {
            return max(query_max(rt<<1,l,mid), query_max(rt<<1|1,mid+1,r));
        }
    }
    // int query_min(int rt,int l,int r) { ///min
    //     push_down(rt);
    
    //     if(l <= t[rt].l && t[rt].r <= r) {
    //         return t[rt].minn;
    //     }
    //     int mid = (t[rt].l + t[rt].r) >> 1;
    //     if(r <= mid) {
    //         return query_min(rt<<1,l,r);
    //     } else if(l > mid) {
    //         return query_min(rt<<1|1,l,r);
    //     } else {
    //         return min(query_min(rt<<1,l,mid), query_min(rt<<1|1,mid+1,r));
    //     }
    // }


    int main(int argc, char const *argv[])
    {
    	freopen("1.in","r", stdin);
    	freopen("std.out", "w", stdout);
        int t;
        //scanf("%d",&t);
        t = read();
        while(t--){
            int n , q;
            //scanf("%d%d",&n,&q);
            n = read(),q = read();
            for(int i = 1;i <= n; i++) //scanf("%d",&a[i]);
                a[i] = read();
            build(1,1,n);
   // //0 cout << 1;
   //  for(int i = 1;i <= n; i++){
   //      cout << t[i].maxx ;
   //  }
            while(q--){
                int a,b,c;
                //scanf("%d%d%d",&a,&b,&c);
                a = read() ,b = read() , c = read();
                if(a == 0){
                    int z;
                    //scanf("%d",&z);
                    z = read();
                    
                    up_date(1,b,c,z);
                }
                else if(a == 1){
                    printf("%d\n",query_max(1,b,c));
                }
                else{
                    printf("%lld\n",query_sum(1,b,c));
                }
            }
        }
        return 0;
    }
    /*
    1
10 8
1323403493 277003437 939437052 1379945413 851723215 195039318 192939579 1144676454 1184299601 1504442346 
1 1 10 
1 1 10 
2 1 10 
0 1 10 813961533
1 1 10 
1 1 10 
0 1 10 412609669
2 1 10 

1
10 3
1323403493 277003437 939437052 1379945413 851723215 195039318 192939579 1144676454 1184299601 1504442346 
0 1 10 813961533
0 1 10 412609669
2 1 10 

1
10 2
1323403493 277003437 939437052 1379945413 851723215 195039318 192939579 1144676454 1184299601 1504442346 
0 1 10 412609669
2 1 10 

    */
