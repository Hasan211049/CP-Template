#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

=========================
Mobius Function μ(n)
=========================

Definition:
-----------
μ(1) = 1

If n has a squared prime factor:
    μ(n) = 0

Else if n is the product of k distinct primes:
    μ(n) = (-1)^k

Examples:
---------
μ(1)  =  1
μ(2)  = -1
μ(3)  = -1
μ(6)  =  1      (2 × 3)
μ(10) =  1      (2 × 5)
μ(30) = -1      (2 × 3 × 5)
μ(12) =  0      (2² divides 12)
μ(18) =  0      (3² divides 18)

-----------------------------------
Linear Sieve Idea
-----------------------------------

Maintain
- prime[]
- isComposite[]
- mobius[]

Initially:
μ(1) = 1

For every i:

If i is prime:
    μ(i) = -1

For every prime p:

    x = i * p

    if p divides i:
        x contains p²
        μ(x) = 0
        break

    else:
        μ(x) = -μ(i)

Time : O(N)
Space: O(N)

==========================================
Most Important Properties
==========================================

1. μ(n) ∈ {-1,0,1}

2. μ(n)=0 -> iff n is NOT square-free.

3. μ(n)^2 = 1 -> iff n is square-free.

4. Σ μ(d) over all divisors d of n
    = 1   if n = 1
    = 0   otherwise

This identity is the heart of Mobius Inversion.

==========================================
Common Uses in Competitive Programming
==========================================

1. Mobius Inversion (kind of prefix sum for divisor's)
-------------------

If

   [f is the prefix sum of all divisor's] 

         f(n) = Σ   {g(d)}
               d|n

then

    g(n) = Σ { μ(d) f(n/d) }
          d|n

Very common in divisor problems.

------------------------------------------

2. Counting Coprime Pairs
-------------------------

Number of pairs (a,b) between [1-m && 1-n]
such that gcd(a,b)=1

        min(n,m)
Formula: Σ μ(d) * floor(n/d) * floor(m/d)
         1
Time:
O(N log log N) preprocessing
O(√N) / O(N) depending on optimization.

------------------------------------------

3. Inclusion-Exclusion over Prime Factors
-----------------------------------------

Mobius automatically performs
inclusion-exclusion on divisors.

Instead of manually adding/subtracting
every subset of prime factors,
μ(n) gives the correct sign.

------------------------------------------

4. Counting Square-Free Numbers
-------------------------------

Number of square-free integers ≤ N

Formula:

Σ μ(i) * floor(N / i²)

Time:
O(√N)

------------------------------------------

5. Dirichlet Convolution
------------------------

Mobius is the inverse of
constant function 1.

1 * μ = ε

where

ε(1)=1
ε(n)=0 (n>1)

Useful in multiplicative functions.

------------------------------------------

6. Euler Totient Formula
------------------------


** Euler Totient-এর একটা theorem আছে : ∑ ϕ(d) =n	​
                                       d|n

** φ(n) = Σ μ(d) * (n/d)
         d|n

------------------------------------------

7. GCD-related Problems
-----------------------

Many problems involving

Σ gcd(i,j)

Σ lcm(i,j)

Σ f(gcd)

can be transformed using μ.

------------------------------------------

8. Number Theory Transformations
--------------------------------

Frequently used in

- Harmonic Lemma
- Divisor Summation
- Multiplicative Functions
- Dirichlet Convolution
- Advanced Number Theory

==========================================
When should you think of Mobius?
==========================================

If you see

✔ gcd(i,j)
✔ coprime
✔ divisor sums
✔ square-free
✔ inclusion-exclusion
✔ multiplicative functions
✔ inversion of divisor relations

then Mobius Function is often the right tool.

*/

const int N = 1e6 + 5;

vector<int> prime;
bool isComposite[N];
int mobius[N];

void mobius_sieve() {

    mobius[1] = 1;

    for (int i = 2; i < N; i++) {

        if (!isComposite[i]) {
            prime.push_back(i);
            mobius[i] = -1;
        }

        for (int p : prime) {

            if (i * p >= N) break;

            isComposite[i * p] = true;

            if (i % p == 0) {
                mobius[i * p] = 0;
                break;
            }
            else {
                mobius[i * p] = -mobius[i];
            }
        }
    }
}

void solve() {

    int n;
    cin >> n;

    cout << mobius[n] << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    mobius_sieve();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}