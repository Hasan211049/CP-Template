#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Chinese Remainder Theorem (CRT)

What it does:
Given n congruences

    x ≡ r1 (mod m1)
    x ≡ r2 (mod m2)
    ...
    x ≡ rn (mod mn)

where all moduli are pairwise coprime, CRT finds the unique solution
modulo M = m1 * m2 * ... * mn.

------------------------------------------------------------

When to use:

1. All moduli are pairwise coprime.
2. Combine multiple modular equations.
3. Multi-mod hashing.
4. Number Theory problems.
5. Construct a number satisfying several remainders.

------------------------------------------------------------

Condition

For every pair i != j,

    gcd(mi, mj) = 1

If this is NOT true, use General CRT instead.

------------------------------------------------------------

Idea

Suppose

x ≡ ri (mod mi)

Let

M = m1 * m2 * ... * mn

For every equation,

Mi = M / mi

Since gcd(Mi, mi)=1,

Mi has an inverse modulo mi.

Multiply

ri × Mi × inv(Mi)

This term

• is congruent to ri modulo mi
• becomes 0 modulo every other modulus

Adding all such terms gives the required answer.

Finally,

answer %= M.

------------------------------------------------------------

Formula

M = Π mi

Answer = Σ (ri × Mi × inv(Mi)) mod M

where

Mi = M / mi

------------------------------------------------------------

Algorithm

1. Compute product M.
2. For every equation
      Mi = M / mi
      inv = Mi⁻¹ mod mi
      ans += ri × Mi × inv
3. Return ans % M.

------------------------------------------------------------

Time Complexity

O(n log M)

------------------------------------------------------------

Space Complexity

O(1)

------------------------------------------------------------

Notes

• Works ONLY when all moduli are pairwise coprime.
• Answer is unique modulo M.
• Uses Extended Euclidean Algorithm for modular inverse.
• Use __int128 for multiplication to avoid overflow.

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

int mod_inverse(int a, int m) {
    int x, y;
    int g = extended_gcd(a, m, x, y);

    // In CRT, inverse always exists because gcd(a,m)=1
    if (g != 1) return -1;

    x %= m;
    if (x < 0) x += m;
    return x;
}

// Returns the smallest non-negative solution.
// Assumes all moduli are pairwise coprime.
int CRT(vector<int> &rem, vector<int> &mods) {

    int n = rem.size();

    int M = 1;
    for (int x : mods)
        M *= x;

    __int128 ans = 0;

    for (int i = 0; i < n; i++) {

        int Mi = M / mods[i];
        int inv = mod_inverse(Mi, mods[i]);

        ans += (__int128)rem[i] * Mi * inv;
    }

    ans %= M;

    if (ans < 0) ans += M;

    return (int)ans;
}

void solve() {

    int n;
    cin >> n;

    vector<int> rem(n), mods(n);

    for (int i = 0; i < n; i++)
        cin >> rem[i] >> mods[i];

    cout << CRT(rem, mods) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}