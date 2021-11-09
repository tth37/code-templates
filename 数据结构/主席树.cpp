// 数据结构-主席树（历史版本查询区间和）
#include <iostream>
#include <algorithm>
using namespace std;
typedef int ll;

const int N = 1e5 + 5;

struct Persistent_Seg {
    struct Node {
        int l, r;
        ll val;
    } node[N << 3];
#define lson(u) node[u].l
#define rson(u) node[u].r
#define val(u) node[u].val
    int R[N], cnt;
    // 建树
    void build(int& u, int l, int r) {
        u = ++cnt;
        val(u) = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(lson(u), l, mid);
        build(rson(u), mid + 1, r);
    }
    // 向上更新
    void pushup(int u) {
        val(u) = val(lson(u)) + val(rson(u));
    }
    // 在 p 点处加 x
    void insert(int& u, int v, int l, int r, int p, ll x) {
        u = ++cnt;
        if (l == r) {
            val(u) = val(v) + x;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) insert(lson(u), lson(v), l, mid, p, x), rson(u) = rson(v);
        else insert(rson(u), rson(v), mid + 1, r, p, x), lson(u) = lson(v);
        pushup(u);
    }
    // 查询区间 [ql, qr] 和
    ll querySum(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return val(u);
        }
        int mid = (l + r) >> 1;
        ll ret = 0;
        if (ql <= mid) ret += querySum(lson(u), l, mid, ql, qr);
        if (mid < qr) ret += querySum(rson(u), mid + 1, r, ql, qr);
        return ret;
    }
} T;
