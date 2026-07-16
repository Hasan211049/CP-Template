#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Bitwise Sieve

Idea:
- Ignore all even numbers except 2.
- One bit represents whether an odd number is composite.
- If bit = 1 -> Composite
- If bit = 0 -> Prime

Bit Operations:
Check bit:
    mark[x >> 5] & (1 << (x & 31))

Set bit:
    mark[x >> 5] |= (1 << (x & 31))

Why x>>5 ?
- One int = 32 bits.
- x>>5 = x/32 gives the integer index.

Why x&31 ?
- x%32 gives the bit position.

Time Complexity:
O(N log log N)

Space Complexity:
O(N / 64)
(Only odd numbers are stored.)

*/

const int N = 1000000 + 5;

int mark[(N >> 5) + 5];
vector<int> primes;

bool isComposite(int x) {
    return mark[x >> 5] & (1 << (x & 31));
}

void setComposite(int x) {
    mark[x >> 5] |= (1 << (x & 31));
}

void bitwiseSieve() {

    primes.push_back(2);

    for (int i = 3; i * i < N; i += 2) {

        if (!isComposite(i)) {

            for (int j = i * i; j < N; j += (i << 1))
                setComposite(j);
        }
    }

    for (int i = 3; i < N; i += 2)
        if (!isComposite(i))
            primes.push_back(i);
}

void solve() {

    int n;
    cin >> n;

    if (n == 2)
        cout << "Prime\n";
    else if (n < 2 || n % 2 == 0)
        cout << "Not Prime\n";
    else if (!isComposite(n))
        cout << "Prime\n";
    else
        cout << "Not Prime\n";
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    bitwiseSieve();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}