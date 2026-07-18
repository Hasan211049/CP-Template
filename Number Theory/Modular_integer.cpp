#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Modular Integer (Mint Struct)

Idea:
Instead of manually taking modulo after every operation, we create a custom
integer type (`mint`) that automatically performs all arithmetic modulo `mod`.

It supports:
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Fast exponentiation
- Modular inverse

Every value is always maintained in the range [0, mod-1].

--------------------------------------------------------
Constructor

mint(long long v = 0)

Converts any integer into its modulo equivalent.

Example (mod = 7):

10  -> 3
15  -> 1
-2  -> 5

Implementation:

x = v % mod;
if (x < 0) x += mod;

--------------------------------------------------------
Addition

(a + b) % mod

Since

0 <= a,b < mod

their sum is always less than 2*mod.

So only one subtraction is enough.

Complexity:
O(1)

--------------------------------------------------------
Subtraction

(a - b) % mod

If the result becomes negative,
simply add mod once.

Complexity:
O(1)

--------------------------------------------------------
Multiplication

(a * b) % mod

Complexity:
O(1)

Note:
For mod = 1e9+7 and long long,
(a*b) safely fits inside signed 64-bit.

--------------------------------------------------------
Fast Power

power(a,p)

Computes

a^p mod mod

using Binary Exponentiation.

Complexity:
O(log p)

--------------------------------------------------------
Modular Inverse

inv()

Uses Fermat's Little Theorem:

a^(mod-2) ≡ a^(-1) (mod mod)

Works ONLY when:
- mod is prime
- gcd(a, mod) = 1

Complexity:
O(log mod)

--------------------------------------------------------
Division

a / b

=

a * inverse(b)

Complexity:
O(log mod)

--------------------------------------------------------
Operator Overloading

Supports natural arithmetic:

mint a = 5;
mint b = 3;

cout << a + b << '\n';
cout << a - b << '\n';
cout << a * b << '\n';
cout << a / b << '\n';

instead of repeatedly writing

(a+b)%mod
(a-b+mod)%mod
(a*b)%mod

--------------------------------------------------------
When to use

✓ Modular DP
✓ Combinatorics (nCr)
✓ Number Theory
✓ Matrix Exponentiation
✓ Polynomial / NTT
✓ Graph Problems involving modulo
✓ Any problem requiring repeated modulo operations

solve function() {

    mint a = 10;
    mint b = 20;

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    cout << "\nBasic Operations\n";

    cout << "a + b = " << a + b << '\n';
    cout << "a - b = " << a - b << '\n';
    cout << "a * b = " << a * b << '\n';
    cout << "a / b = " << a / b << '\n';

    cout << "\nCompound Operations\n";

    mint c = a;

    c += b;
    cout << "a += b : " << c << '\n';

    c = a;
    c -= b;
    cout << "a -= b : " << c << '\n';

    c = a;
    c *= b;
    cout << "a *= b : " << c << '\n';

    c = a;
    c /= b;
    cout << "a /= b : " << c << '\n';

    cout << "\nPower & Inverse\n";

    cout << "2^10 = " << mint::power(2, 10) << '\n';

    mint x = 5;
    cout << "Inverse of 5 = " << x.inv() << '\n';
    cout << "5 * inv(5) = " << x * x.inv() << '\n';

    cout << "\nNegative Number Example\n";

    mint neg = -15;
    cout << "-15 mod = " << neg << '\n';

    cout << "\nInput Example\n";

    mint y;
    cin >> y;
    cout << "You entered : " << y << '\n';
}

*/

struct mint {

    int x;

    mint(int v = 0) {
        x = v % mod;
        if (x < 0) x += mod;
    }

    mint& operator+=(const mint &b) {
        x += b.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint& operator-=(const mint &b) {
        x -= b.x;
        if (x < 0) x += mod;
        return *this;
    }

    mint& operator*=(const mint &b) {
        x = (x * b.x) % mod;
        return *this;
    }

    static mint power(mint a, int p) {
        mint res = 1;
        while (p) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }

    mint inv() const {
        return power(*this, mod - 2);
    }

    mint& operator/=(const mint &b) {
        return *this *= b.inv();
    }

    friend mint operator+(mint a, const mint &b) {
        return a += b;
    }

    friend mint operator-(mint a, const mint &b) {
        return a -= b;
    }

    friend mint operator*(mint a, const mint &b) {
        return a *= b;
    }

    friend mint operator/(mint a, const mint &b) {
        return a /= b;
    }

    friend ostream& operator<<(ostream &os, const mint &a) {
        return os << a.x;
    }

    friend istream& operator>>(istream &is, mint &a) {
        int v;
        is >> v;
        a = mint(v);
        return is;
    }
};

void solve() {
    
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}