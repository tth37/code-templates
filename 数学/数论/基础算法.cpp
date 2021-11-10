const int N = 1e6 + 10;
long long mul_mod(long long a, long long b, long long p) {
    unsigned long long ans =
        (unsigned long long)a * b - (unsigned)((long double)a / p * b + 0.5L) * p;
    return (ans + p) % p;
}
long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    long long ans = exgcd(b, a % b, x, y);
    long long tmp = x;
    x = y; y = tmp - a / b * y;
    return ans;
}
long long inv_mod(long long a, long long p) {
    long long x, y;
    long long d = exgcd(a, p, x, y);
    return (d == 1) ? (x + p) % p : -1;
}
long long pow_mod(long long a, long long n, long long p) {
    a %= p;
    long long ans = 1LL;
    while (n) {
        if (n & 1) ans = mul_mod(ans, a, p);
        a = mul_mod(a, a, p);
        n >>= 1;
    }
    return inv_mod(ans, p);
}
long long inv_12n[N];
void get_inv_12n(int n, long long p) {
    inv_12n[1] = 1;
    for (int i = 2; i <= n; i++)
        inv_12n[i] = mul_mod((long long)(p - p / i), inv_12n[p % i], p);
}
long long factorials[N], inv_factorials[N];
long long C_pre(int n, long long p) {
    factorials[0] = 1ll; inv_factorials[0] = 1ll;
    for (int i = 1; i <= n; i++)
        factorials[i] = mul_mod(factorials[i - 1], (long long) i, p);
    inv_factorials[n] = inv_mod(factorials[n], p);
    for (int i = n; i; i--)
    	inv_factorials[i - 1] = mul_mod(inv_factorials[i], (long long) i, p);
}
long long C(long long n, long long m, long long p) {
	return mul_mod(factorials[n], mul_mod(inv_factorials[n - m], inv_factorials[m], p), p);
}
long long Lucas(long long n, long long m, long long p) {
    if (m == 0) return 1;
    return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}