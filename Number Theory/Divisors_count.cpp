#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;
const int N = 1e6 + 9;

int d[N];   // d[i] = number of divisors of i

/*Explanation :

-> Known as Harmonic number

Purpose:
- Precomputes the number of divisors for every number from
  1 to N-1.

Idea:
Instead of finding divisors for each number separately,
visit every multiple of every integer.

Suppose

i = 3

Then

3 divides

3, 6, 9, 12, 15, ...

So increase the divisor count of every multiple of 3.

Similarly,

1 divides every number.
2 divides every multiple of 2.
4 divides every multiple of 4.

Every divisor contributes exactly once.


Time Complexity :

Outer Loop : N

Inner Loop :

N/1 + N/2 + N/3 + ...

= N × (1 + 1/2 + 1/3 + ...)

= N × H(N)

≈ O(N log N)


Space : O(N)

-

*/

void prec() {

    for (int i = 1; i < N; i++) {

        for (int j = i; j < N; j += i) {

            d[j]++;
        }
    }
}

void solve() {

    int n;
    cin >> n;

    cout << d[n] << '\n';
}

int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    prec();

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}