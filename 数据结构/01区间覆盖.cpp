// 数据结构-01区间覆盖（只含有 1 的 01 区间覆盖问题）
#include <iostream>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

struct Data_structure {
    int f[N], a[N], sum;
    // 初始化（默认为 0）
    void build(int n) {
        sum = 0;
        for (int i = 1; i <= n; ++i)
            f[i] = i, a[i] = 0;
    }
    // 求 1 的数量
    int getSum() {
        return sum;
    }
    int findf(int u) {
        if (f[u] == u) return u;
        return f[u] = findf(f[u]);
    }
    // 将区间 [l, r] 修改为 1
    void modify(int l, int r) {
        for (int i = l; i <= r; ++i) {
            if (a[i] == 0) {
                a[i] = 1, sum++;
                f[findf(i)] = findf(r);
            } else {
                i = findf(i);
                f[findf(i)] = findf(r);
            }
        }
        if (a[r + 1]) f[findf(r)] = findf(r + 1);
        if (a[l - 1]) f[findf(l - 1)] = findf(r);
    }
} T;
233
