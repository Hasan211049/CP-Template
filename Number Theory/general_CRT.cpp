#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Chinese Remainder Theorem (CRT)

What it does:
Given several congruences,

    x ≡ r1 (mod m1)
    x ≡ r2 (mod m2)
    ...
    x ≡ rn (mod mn)

CRT finds the smallest non-negative x satisfying all equations.

------------------------------------------------------------

When to use:

1. Solve multiple modular equations simultaneously.
2. Combine answers computed under different moduli.
3. Number Theory problems.
4. Garner Algorithm base.
5. Pollard-Rho / Miller-Rabin related problems.
6. Multi-mod hashing.

------------------------------------------------------------

Types of CRT

Case 1:
All moduli are pairwise coprime.

Example:
x ≡ 2 (mod 3)
x ≡ 3 (mod 5)

Unique solution modulo (3×5)=15.

------------------------------------------------------------

Case 2:
Moduli are NOT coprime.

Example:
x ≡ 2 (mod 6)
x ≡ 8 (mod 12)

A solution may or may not exist.

General CRT handles this case.

------------------------------------------------------------

Idea (General CRT)

Suppose we already know

x ≡ r1 (mod m1)

Now merge

x ≡ r2 (mod m2)

Write

x = r1 + k*m1

Substitute into second equation

r1 + k*m1 ≡ r2 (mod m2)

=> k*m1 ≡ (r2-r1) (mod m2)

This is a linear congruence.

Let

g = gcd(m1,m2)

If

(r2-r1)%g != 0

then NO solution exists.

Otherwise,

divide everything by g and solve using modular inverse.

The merged equation becomes

x ≡ newR (mod lcm(m1,m2))

Repeat for every equation.

------------------------------------------------------------

Algorithm

Initially

ans = r1
lcm = m1

For every equation

1. Compute gcd(lcm,m)
2. Check consistency
3. Solve for k
4. Update answer
5. Update lcm

------------------------------------------------------------

Return

(answer, lcm)

Meaning

x = answer + k*lcm

for every integer k.

------------------------------------------------------------

Time Complexity

Each merge:
O(log(min(m1,m2)))

Overall:
O(n log M)

------------------------------------------------------------

Space Complexity

O(1)

------------------------------------------------------------

Notes

• Works for both coprime and non-coprime moduli.
• Returns {-1,-1} if no solution exists.
• Uses Extended Euclid to compute modular inverse.
• Result is always normalized into [0,lcm).

*/

int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

int mod_inverse(int a, int mod) {
    int x, y;
    extended_gcd(a, mod, x, y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

// returns {remainder, modulus}
// {-1,-1} => No solution
pair<int,int> CRT(vector<int> &r, vector<int> &m) {

    int ans = r[0];
    int lcm = m[0];

    for (int i = 1; i < (int)r.size(); i++) {

        int x, y;
        int g = extended_gcd(lcm, m[i], x, y);

        if ((r[i] - ans) % g != 0)
            return {-1, -1};

        int mod2 = m[i] / g;

        int k = ((__int128)(r[i] - ans) / g * mod_inverse(lcm / g, mod2)) % mod2;

        if (k < 0) k += mod2;

        ans += k * lcm;
        lcm = lcm / g * m[i];

        ans %= lcm;
        if (ans < 0) ans += lcm;
    }

    return {ans, lcm};
}

void solve() {

    int n;
    cin >> n;

    vector<int> rem(n), mod(n);

    for (int i = 0; i < n; i++)
        cin >> rem[i] >> mod[i];

    auto [ans, lcm] = CRT(rem, mod);

    if (ans == -1)
        cout << "No Solution\n";
    else
        cout << ans << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}