struct DSU {
    vector<int> fa;
    vector<int> sz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        fa.resize(n + 5);
        iota(all(fa), 0);
        sz.resize(n + 5);
        fill(all(sz), 1);
        sz[0] = 0;
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) return 0;
        if (sz[fx] > sz[fy]) {
            swap(x, y);
            swap(fx, fy);
        }
        fa[fx] = fy;
        sz[fy] += sz[fx];
        return 1;
    }
    int size(int x) {
        return sz[find(x)];
    }
};