#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Lucas Theorem

When to use:
- Compute C(n, r) mod p where:
    • n, r can be extremely large (up to 10^18 or more).
    • p is a SMALL PRIME.
- Normal factorial method only works when n < p.
- Lucas theorem breaks a huge combination into many small combinations.

Requirement:
- p must be PRIME.
- Efficient only when p is relatively small (typically <= 2e5).

------------------------------------------------------------

Idea:

Suppose we want : C(n, r) mod p

   -> where n is huge.
   -> Write n and r in base p.

Example:

n = 100
r = 37
p = 5

100(base10) = 400(base5)
37(base10)  = 122(base5)

Lucas theorem says

C(n,r) = Π C(ni,ri) (mod p)

where ->
ni = ith digit of n in base p
ri = ith digit of r in base p

So instead of one huge combination,
we solve several tiny combinations.

------------------------------------------------------------

Why does this work?

Suppose

n = a0 + a1*p + a2*p² + ...
r = b0 + b1*p + b2*p² + ...

Lucas proved

C(n,r) ≡ C(a0,b0) × C(a1,b1) × C(a2,b2) ... (mod p)

Each ai and bi is less than p.

Therefore every small combination can be computed
using ordinary factorials.

------------------------------------------------------------

Step-by-step intuition

Example:

Find

C(100,37) mod 5

Convert to base 5

100 = (4 0 0)
37  = (1 2 2)

Now compute

C(0,2)=0

Immediately answer becomes 0.

Reason:
Cannot choose 2 from 0.

------------------------------------------------------------

Another example

Find

C(25,10) mod 7

25 = (34)_7

10 = (13)_7

Answer
= C(4,3) × C(3,1)
= 4 × 3
= 12 mod 7
=5
------------------------------------------------------------

Algorithm

Precompute : fact[i] , invFact[i] 
for : 0 ≤ i < p

Then : Lucas(n,r):

if r==0 return 1

ni = n % p
ri = r % p

return

Lucas(n/p,r/p)
*
C(ni,ri)

mod p

Recursion depth is only

O(log_p n)

------------------------------------------------------------

Complexity

Precomputation:
O(p)

Each query:
O(log_p n)

Memory:
O(p)

------------------------------------------------------------

Limitations

✓ p must be prime.

✓ p should be reasonably small.

✗ Does NOT work for composite modulus.

For composite modulus,
use:
- CRT
- Extended Lucas
- Lucas + CRT

*/

int power(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

vector<int> fact, invFact;

void init(int p) {
    fact.assign(p, 1);
    invFact.assign(p, 1);

    for (int i = 1; i < p; i++)
        fact[i] = fact[i - 1] * i % p;

    invFact[p - 1] = power(fact[p - 1], p - 2, p);

    for (int i = p - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % p;
}

int nCrSmall(int n, int r, int p) {
    if (r > n) return 0;
    return fact[n] * invFact[r] % p * invFact[n - r] % p;
}

int Lucas(int n, int r, int p) {
    if (r == 0) return 1;

    int ni = n % p;
    int ri = r % p;

    if (ri > ni) return 0;

    return Lucas(n / p, r / p, p) * nCrSmall(ni, ri, p) % p;
}

void solve() {
    int n, r, p;
    cin >> n >> r >> p;

    init(p);

    cout << Lucas(n, r, p) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}