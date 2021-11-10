#include<cstdio>
#include<algorithm>
#include<vector>
#include<random>

const int MAXN = 65;
const int test_times = 10;
long long x[MAXN];
std::vector<long long> f;

//2, 3, 7, 61和24251作为底数，那么10^16内唯一的强伪素数为46856248255981ll
//小于4 759 123 141，那么只需要测试三个底数2, 7和61
std::mt19937_64 randomer(std::random_device());
bool Miller_Rabin(long long x) {
	if (x < 3 || x % 2 == 0) return x == 2;
	int a = x - 1, b = 0;
	while (a % 2 == 0) {a /= 2; b++;}
	std::uniform_int_distribution<long long> random_distributor(2, x - 1);
	for (int i = 1, j; i <= test_times; i++) {
		int k = random_distributor(randomer), v = pow_mod(k, a, x);
		if (v == 1) continue;
		for (j = 0; j < b; j++) {
			if (v == x - 1) break;
			v = mul_mod(v, v, x);
		}
		if (j >= b) return false;
	}
	return true;
}

long long Pollard_Rho(long long n, int c) {
	long long i = 1, k = 2, x = rand() % (n - 1) + 1, y = x;
	while (true) {
		i++;
		x = (mul_mod(x, x, n) + c) % n;
		long long p = std::__gcd((y - x + n) % n, n);
		if (p != 1 && p != n) return p;
		if (y == x) return n;
		if (i == k) {
			y = x;
			k <<= 1;
		}
	}
}

void find(long long n, int c) {
	if (n == 1) return;
	if (Miller_Rabin(n)) {
		f.push_back(n);
		return;
	}
	long long p = n, k = c;
	while (p >= n) p = Pollard_Rho(p, c--);
	find(p, k);
	find(n / p, k);
}