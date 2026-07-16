#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :


Extended Euclidean Algorithm

It finds integers x and y such that: ax + by = gcd(a, b)

Idea:

The normal Euclidean Algorithm computes: gcd(a, b) = gcd(b, a % b)

Extended Euclid additionally keeps track of the coefficients x and y (Bézout's coefficients).

Suppose:

    bx1 + (a % b)y1 = gcd(a, b)

Since,

    a % b = a - (a / b) * b

Substitute:

    bx1 + (a - (a / b) * b)y1

Rearrange:

    ay1 + b(x1 - (a / b) * y1)

Comparing with:

    ax + by = gcd(a, b)

We get,

    x = y1
    y = x1 - (a / b) * y1

These recurrence relations are used in the recursive implementation.

Applications:
1. Modular Inverse
2. Linear Diophantine Equation
3. Chinese Remainder Theorem (CRT)

Time Complexity: O(log(min(a, b)))
Space Complexity: O(log(min(a, b)))

-------------------------------------------------------

Linear Diophantine Equation:

    ax + by = c

Algorithm:
1. Compute gcd(a,b) and coefficients x,y using Extended Euclidean Algorithm.
2. If c % gcd != 0 -> No solution.
3. Otherwise, multiply x and y by (c/gcd).
4. Print one valid solution.

General Solution:

x = x0 + k * (b/g)
y = y0 - k * (a/g)

where
g = gcd(a,b)
k ∈ Z

Edge Cases:
1. a = 0, b = 0, c = 0  -> Infinite Solutions
2. a = 0, b = 0, c != 0 -> No Solution
3. a = 0 or b = 0       -> Works automatically
4. Negative coefficients are also handled.

Time Complexity: O(log(min(a,b)))
Space Complexity: O(log(min(a,b)))

*/

int extendedGCD(int a, int b, int &x, int &y) {

    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;

    int g = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

bool solveDiophantine(int a, int b, int c, int &x, int &y, int &g) {

    // Edge Case : 0x + 0y = c
    if (a == 0 && b == 0) {

        if (c == 0) {
            g = 0;
            x = y = 0;
            return true;        // Infinite solutions
        }

        return false;           // No solution
    }

    g = extendedGCD(abs(a), abs(b), x, y);

    if (c % g != 0)
        return false;

    x *= c / g;
    y *= c / g;

    if (a < 0) x = -x;
    if (b < 0) y = -y;

    return true;
}

void solve() {

    int a, b, c;
    cin >> a >> b >> c;

    int x, y, g;

    if (!solveDiophantine(a, b, c, x, y, g)) {
        cout << "No Solution\n";
        return;
    }

    // 0x + 0y = 0
    if (a == 0 && b == 0 && c == 0) {
        cout << "Infinite Solutions\n";
        return;
    }

    cout << "One Solution:\n";
    cout << "x = " << x << '\n';
    cout << "y = " << y << '\n';

    cout << "\nVerification:\n";
    cout << a << " * " << x << " + "
         << b << " * " << y << " = "
         << a * x + b * y << '\n';

    cout << "\nGeneral Solution:\n";
    cout << "x = " << x << " + k * (" << b / g << ")\n";
    cout << "y = " << y << " - k * (" << a / g << ")\n";
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}