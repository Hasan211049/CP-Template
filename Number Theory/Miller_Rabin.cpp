#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Miller-Rabin Primality Test (Deterministic for 64-bit integers)

Purpose:
- Checks whether a number is prime in O(log³ N).
- Much faster than trial division for large numbers (up to 10^18).

Idea:
Write
    n - 1 = d * 2^s
where d is odd.

For several carefully chosen bases 'a':
    Compute x = a^d mod n

If
    x == 1 or x == n-1
then this base passes.

Otherwise repeatedly square x:
    x = x² mod n

If we ever obtain n-1, this base passes.
Otherwise n is definitely composite.

For 64-bit integers, using the following bases makes the test deterministic:
{2, 325, 9375, 28178, 450775, 9780504, 1795265022}

Time Complexity:
O(k log³ N)
(k = 7 bases)

Space Complexity:
O(1)

Notes:
- Works for every signed 64-bit integer.
- Requires safe modular multiplication to avoid overflow.
- Faster than sqrt(N) primality testing.
*/

using u64 = uint64_t;
using u128 = __uint128_t;

// (a * b) % mod without overflow
u64 mod_mul(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

// (a ^ b) % mod
u64 mod_pow(u64 a, u64 b, u64 mod) {
    u64 res = 1;
    while (b) {
        if (b & 1) res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool MillerRabin(u64 n) {

    if (n < 2) return false;

    // Small primes
    for (u64 p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n % p == 0)
            return n == p;
    }

    u64 d = n - 1;
    int s = 0;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    // Deterministic bases for 64-bit
    for (u64 a : {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}) {

        if (a % n == 0) continue;

        u64 x = mod_pow(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool witness = true;

        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);

            if (x == n - 1) {
                witness = false;
                break;
            }
        }

        if (witness)
            return false;
    }

    return true;
}

void solve() {

    int n;
    cin >> n;

    if (MillerRabin(n))
        cout << "Prime\n";
    else
        cout << "Composite\n";
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}