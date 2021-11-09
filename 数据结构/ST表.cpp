// 数据结构-ST表（区间最小值查询）
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

ll a[N];
int n;

struct Sparse_Table {
    int lg2[N];
    ll st[23][N];
    // 初始化
    void build() {
        lg2[0] = -1;
        for (int i = 1; i <= n; ++i)
            lg2[i] = lg2[i >> 1] + 1;
        for (int i = 1; i <= n; ++i)
            st[0][i] = a[i];
        for (int j = 1; j < 23; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    // 查询区间 [ql, qr] 最小值
    ll query(int ql, int qr) {
        int l = lg2[qr - ql + 1];
        return max(st[l][ql], st[l][qr - (1 << l) + 1]);
    }
} T;
