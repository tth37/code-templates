// 数据结构-SegmentTreeBeats（区间取 min，区间和查询）
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int a[N], n;

struct Segment_Tree_Beats {
    struct Node {
        int l, r, mx, se, t;
        ll s;
    } node[N << 1];
#define lson(u) node[u].l
#define rson(u) node[u].r
#define mx(u) node[u].mx
#define se(u) node[u].se
#define t(u) node[u].t
#define s(u) node[u].s
    int R, cnt;
    // 向上更新
    void pushup(int u) {
        if (mx(lson(u)) == mx(rson(u))) {
            mx(u) = mx(lson(u));
            t(u) = t(lson(u)) + t(rson(u));
            se(u) = max(se(lson(u)), se(rson(u)));
        } else if (mx(lson(u)) > mx(rson(u))) {
            mx(u) = mx(lson(u));
            t(u) = t(lson(u));
            se(u) = max(mx(rson(u)), se(lson(u)));
        } else {
            mx(u) = mx(rson(u));
            t(u) = t(rson(u));
            se(u) = max(mx(lson(u)), se(rson(u)));
        }
        s(u) = s(lson(u)) + s(rson(u));
    }
    // 建树
    void build(int& u, int l, int r) {
        u = ++cnt;
        if (l == r) {
            mx(u) = s(u) = a[l];
            se(u) = -1;
            t(u) = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson(u), l, mid);
        build(rson(u), mid + 1, r);
        pushup(u);
    }
    // 查询区间 [ql, qr] 和
    ll query_sum(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return s(u);
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        ll ret = 0;
        if (ql <= mid) ret += query_sum(lson(u), l, mid, ql, qr);
        if (mid < qr) ret += query_sum(rson(u), mid + 1, r, ql, qr);
        return ret;
    }
    // 查询区间 [ql, qr] 最大值
    int query_max(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return mx(u);
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        int ret = -1;
        if (ql <= mid) ret = max(ret, query_max(lson(u), l, mid, ql, qr));
        if (mid < qr) ret = max(ret, query_max(rson(u), mid + 1, r, ql, qr));
        return ret;
    }
    // 标记下传
    void pushdown(int u) {
        update(lson(u), mx(u));
        update(rson(u), mx(u));
    }
    // 更新当前节点
    void update(int u, int x) {
        if (x >= mx(u)) return;
        s(u) -= 1ll * t(u) * (mx(u) - x);
        mx(u) = x;
    }
    // 区间 [ql, qr] 对 x 取 min
    void modify(int u, int l, int r, int ql, int qr, int x) {
        if (x >= mx(u)) return;
        if (ql <= l && r <= qr && x >= se(u)) {
            update(u, x);
            return;
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(lson(u), l, mid, ql, qr, x);
        if (mid < qr) modify(rson(u), mid + 1, r, ql, qr, x);
        pushup(u);
    }
} T;
