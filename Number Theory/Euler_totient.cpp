#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Euler Totient Function (φ)

Definition:
φ(n) = Number of integers in [1, n] that are coprime with n.

Formula:
φ(n) = n × ∏ (1 - 1/p)
where p are the distinct prime factors of n.

Idea:
1. Build SPF using Linear Sieve.
2. Extract distinct prime factors of n.
3. Apply:
      phi -= phi / p

Time Complexity:
Build SPF : O(N)
Each Query : O(log N)

Space Complexity:
O(N)

*/

const int N = 1e6 + 5;

vector<int> spf(N);
vector<int> primes;

// It precompute's all phi value form [0,,n-1] 
// Build : O(n logn ) ; query : O(1)

 /* void buildPhi() {
    for (int i = 0; i < N; i++)
        phi[i] = i;

    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {          // i is prime
            for (int j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
} */




void buildSPF() {
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

int phi(int n) {

    int res = n;

    while (n > 1) {

        int p = spf[n];

        res -= res / p;

        while (n % p == 0)
            n /= p;
    }

    return res;
}

void solve() {

    int n;
    cin >> n;

    cout << phi(n) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    buildSPF();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}