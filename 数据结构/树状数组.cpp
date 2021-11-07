// 数据结构-树状数组（单点修改，前缀和查询）
struct BIT {
    ll c[MAXN];
    // 在位置 p 上加 val
    void modify(int p, ll val) {
        for (; p <= n; p += p & (-p)) {
            c[p] += val;
        }
    }
    // 查询位置 p 的前缀和
    ll query(int p) {
        ll ret = 0;
        for (; p > 0; p -= p & (-p)) {
            ret += c[p];
        }
        return ret;
    }
} T;
