// 数据结构-线段树（区间加，区间和查询）
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Segment_Tree {
    struct Node {
        int l, r;
        ll val, tag;
    } node[N << 2];
#define lson(u) node[u].l
#define rson(u) node[u].r
#define val(u) node[u].val
#define tag(u) node[u].tag
    int R, cnt;
    // 建树
    void build(int& u, int l, int r) {
        u = ++cnt;
        val(u) = tag(u) = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(lson(u), l, mid);
        build(rson(u), mid + 1, r);
    }
    // 标记下传
    void pushdown(int u, int l, int r) {
        if (tag(u) == 0) return;
        int mid = (l + r) >> 1;
        ll llen = mid - l + 1, rlen = r - mid;
        val(lson(u)) += llen * tag(u);
        tag(lson(u)) += tag(u);
        val(rson(u)) += rlen * tag(u);
        tag(rson(u)) += tag(u);
        tag(u) = 0;
    }
    // 向上更新
    void pushup(int u) {
        val(u) = val(lson(u)) + val(rson(u));
    }
    // 区间 [ql, qr] 上加 x
    void modify(int u, int l, int r, int ql, int qr, ll x) {
        if (ql <= l && r <= qr) {
            val(u) += 1ll * (r - l + 1) * x;
            tag(u) += x;
            return;
        }
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(lson(u), l, mid, ql, qr, x);
        if (mid < qr) modify(rson(u), mid + 1, r, ql, qr, x);
        pushup(u);
    }
    //查询区间 [ql, qr] 和
    ll query(int u, int l, int r, int ql, int qr) {
        cout << l << ' ' << r << ' ' << val(u) << endl;
        if (ql <= l && r <= qr) {
            return val(u);
        }
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        ll ret = 0;
        if (ql <= mid) ret += query(lson(u), l, mid, ql, qr);
        if (mid < qr) ret += query(rson(u), mid + 1, r, ql, qr);
        return ret;
    }
} T;
