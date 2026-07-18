#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Pollard-Rho Integer Factorization

Definition:
Pollard-Rho is a randomized integer factorization algorithm used to find a
non-trivial factor (1 < d < n) of a composite number efficiently.

It is one of the fastest practical algorithms for factoring 64-bit integers
(up to 10^18).

------------------------------------------------------------

When to Use?

Use Pollard-Rho when:

• n can be as large as 10^18.
• Trial Division (O(sqrt(n))) is too slow.
• You need the prime factorization of a large integer.

Typical applications:
- Prime Factorization
- Largest Prime Factor
- Number of Divisors
- Sum of Divisors
- Euler Totient φ(n)
- Möbius Function
- Generate All Divisors
- Any problem requiring prime factors of a 64-bit integer

Usually used together with Miller-Rabin:

Miller-Rabin
    ↓
Checks whether n is prime.

Pollard-Rho
    ↓
Finds one non-trivial factor if n is composite.

------------------------------------------------------------

Idea

Instead of checking every divisor,

Pollard-Rho generates a pseudo-random sequence

    x(i+1) = (x(i)^2 + c) mod n

using a random constant c.

For every composite number

    n = p × q

the sequence forms cycles modulo p and modulo q.

Eventually,

    slow ≡ fast (mod p)

before

    slow ≡ fast (mod n)

Therefore,

    p | (slow-fast)

Taking

    gcd(|slow-fast|, n)

reveals a non-trivial factor.

------------------------------------------------------------

Why the name "Rho"?

The generated sequence eventually enters a cycle.

The shape of the path resembles the Greek letter

ρ (rho)

Hence the name Pollard-Rho.

------------------------------------------------------------

Why Floyd Cycle Detection?

We don't store every generated value.

Instead,

slow = f(slow)

fast = f(f(fast))

When they meet modulo a prime factor,

gcd(|slow-fast|, n)

reveals that factor.

Memory becomes O(1).

------------------------------------------------------------

Workflow

factor(n)

↓

Prime?
      │
 ┌────┴─────┐
 │          │
Yes         No
 │          │
Store n     │
            ▼
     Pollard-Rho
            │
            ▼
   Find one factor d
            │
     ┌──────┴──────┐
     ▼             ▼
 factor(d)   factor(n/d)

Repeat until every factor becomes prime.

------------------------------------------------------------

Randomization

Different runs may use different

- starting value x
- constant c

If one sequence fails (gcd == n),

restart with another random sequence.

This makes the algorithm very effective in practice.

------------------------------------------------------------

Important Functions

mulmod()
    Safe modular multiplication using __int128.

power()
    Binary Modular Exponentiation.

isPrime()
    Deterministic Miller-Rabin for 64-bit integers.

pollard_rho()
    Finds one non-trivial factor.

factor()
    Recursively computes the complete prime factorization.

------------------------------------------------------------

Time Complexity

Miller-Rabin:
O(log n)

Pollard-Rho (Expected):
O(n^(1/4))

Overall factorization of 64-bit integers is extremely fast in practice.

------------------------------------------------------------

Space Complexity

O(log n)

(recursion depth)

------------------------------------------------------------

Notes

• Randomized (Las Vegas) Algorithm.
• Always returns correct factors.
• Running time is probabilistic.
• Uses __int128 to avoid overflow.
• Standard implementation for integer factorization up to 10^18.

*/

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int mulmod(int a, int b, int m) {
    return (__int128)a * b % m;
}

int power(int a, int d, int m) {
    int res = 1;
    while (d) {
        if (d & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        d >>= 1;
    }
    return res;
}

bool isPrime(int n) {
    if (n < 2) return false;

    for (int p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n % p == 0) return n == p;
    }

    int d = n - 1;
    int s = 0;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int a : {2,325,9375,28178,450775,9780504,1795265022}) {

        if (a % n == 0) continue;

        int x = power(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool ok = false;

        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);

            if (x == n - 1) {
                ok = true;
                break;
            }
        }

        if (!ok) return false;
    }

    return true;
}

int f(int x, int c, int mod) {
    return (mulmod(x, x, mod) + c) % mod;
}

int pollard_rho(int n) {

    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    while (true) {

        int x = uniform_int_distribution<int>(2, n - 2)(rng);
        int y = x;
        int c = uniform_int_distribution<int>(1, n - 1)(rng);

        int d = 1;

        while (d == 1) {

            x = f(x, c, n);
            y = f(f(y, c, n), c, n);

            d = gcd(abs(x - y), n);
        }

        if (d != n)
            return d;
    }
}

vector<int> factors;

void factor(int n) {

    if (n == 1)
        return;

    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }

    int d = pollard_rho(n);

    factor(d);
    factor(n / d);
}

void solve() {

    int n;
    cin >> n;

    factors.clear();

    factor(n);

    sort(factors.begin(), factors.end());

    for (int x : factors)
        cout << x << ' ';
    cout << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--)
        solve();

    return 0;
}