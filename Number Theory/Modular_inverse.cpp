#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Modular Inverse using Fermat's Little Theorem.

Condition:
1. mod must be prime.
2. gcd(a, mod) = 1.

Formula:
a^(-1) = a^(mod-2) % mod

Time Complexity: O(log mod)
Space Complexity: O(1)

*/

int binExp(int base, int power) {

    base %= mod;
    int ans = 1;

    while (power > 0) {

        if (power & 1)
            ans = (ans * base) % mod;

        base = (base * base) % mod;
        power >>= 1;
    }

    return ans;
}

int modInverse(int a) {
    return binExp(a, mod - 2);
}

void solve() {

    int a;
    cin >> a;

    cout << modInverse(a) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}