#include<cstring>
const int N = 1e6 + 10;
int phi[N], mu[N], primes[N], cnt = 0;
bool is_prime[N];
void linear_sieve(int n) {
    phi[1] = 1; mu[1] = 1; memset(is_prime, true, sizeof is_prime); is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= n; j++) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j]) {
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
                mu[i * primes[j]] = -mu[i];
            }
            else {
                phi[i * primes[j]] = phi[i] * primes[j];
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
}