#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Binary Exponentiation computes a^b in O(log b).

Time Complexity: O(log b)
Space Complexity: O(1)

*/

int power(int base, int exp) {
    int ans = 1;

    while (exp > 0) {
        if (exp & 1)
            ans *= base;

        base *= base;
        exp >>= 1;
    }

    return ans;
}

void solve() {

    int a, b;
    cin >> a >> b;

    cout << power(a, b) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}