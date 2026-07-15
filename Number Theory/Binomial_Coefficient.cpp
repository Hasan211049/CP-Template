#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;
const int N = 1e6 + 9;

int fact[N], inv[N], invFact[N];

/*Explanation :

Purpose:
- Computes nCr % mod for multiple queries efficiently.
- Works only when mod is PRIME.

Idea:
We know,

                n!
nCr = -------------------
      r! * (n-r)!

Modulo division is not allowed directly.
Instead,

a / b ≡ a × b^(-1) (mod mod)

So,

nCr = fact[n] × invFact[r] × invFact[n-r]

where

invFact[i] = (i!)^(-1)

Instead of computing every inverse using Binary Exponentiation
(O(N log MOD)), we compute all modular inverses in O(N).

Formula:

inv[i] = -(mod / i) × inv[mod % i] (mod mod)

Then,

invFact[i]
= invFact[i-1] × inv[i]


Time Complexity:
Preprocessing : O(N)
Each Query    : O(1)

Space Complexity:
O(N)



Requirements:
- mod must be PRIME.
- n < N.

*/

void prec() {

    // factorial
    fact[0] = 1;

    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i % mod;

    // modular inverse
    inv[1] = 1;

    for (int i = 2; i < N; i++) {
        inv[i] = (-(mod / i) * inv[mod % i]) % mod;
        inv[i] = (inv[i] + mod) % mod;
    }

    // inverse factorial
    invFact[0] = 1;

    for (int i = 1; i < N; i++)
        invFact[i] = invFact[i - 1] * inv[i] % mod;
}

int nCr(int n, int r) {

    if (r < 0 || n < 0 || r > n)
        return 0;

    return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}

void solve() {

    int n, r;
    cin >> n >> r;

    cout << nCr(n, r) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    prec();

    int t = 1;
    cin >> t;

    while (t--)
        solve();

    return 0;
}