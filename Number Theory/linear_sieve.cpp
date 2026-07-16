#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Linear Sieve (Euler Sieve)

Idea:
- Every composite number is marked exactly once using its
  smallest prime factor (SPF).
- Maintain:
    1. primes -> stores all prime numbers
    2. spf[i] -> smallest prime factor of i

Algorithm:
1. Traverse i = 2 to N-1.
2. If spf[i] == 0, then i is prime.
      spf[i] = i
      primes.push_back(i)
3. For every prime p:
      if (p > spf[i] || i * p >= N) break;
      spf[i * p] = p;

Time Complexity:
O(N)

Space Complexity:
O(N)

Applications:
- Prime checking
- Prime factorization in O(log N)
- Number of divisors
- Euler Phi
- Mobius Function

*/

const int N = 1e6 + 5;

vector<int> primes;
vector<int> spf(N, 0);

void linearSieve() {
    
    spf[0] = spf[1] = 1;

    for (int i = 2; i < N; i++) {

        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > spf[i] || i * p >= N) break;
            spf[i * p] = p;
        }
    }
}

vector<int> primeFactorization(int n) {
    vector<int> factors;
    while (n > 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}

void solve() {
    int n;
    cin >> n;

    if (spf[n] == n)
        cout << "Prime\n";
    else
        cout << "Not Prime\n";

    vector<int> factors = primeFactorization(n);

    for (int x : factors)
        cout << x << ' ';
    cout << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    linearSieve();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}