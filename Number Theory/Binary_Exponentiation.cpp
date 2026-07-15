#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Purpose:
- Computes (x^n) % mod efficiently.


Time Complexity:
- O(log n)

Space Complexity:
- O(1)


Notes:
- If negative bases are possible, use:
      x = (x % mod + mod) % mod;

*/

int power(int x, int n) {

    x %= mod;
    int ans = 1;

    while (n > 0) {

        if (n & 1)
            ans = ans * x % mod;

        x = x * x % mod;
        n >>= 1;
    }

    return ans;
}

void solve() {

    int x, n;
    cin >> x >> n;

    cout << power(x, n) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
  //  cin >> t;

    while (t--)
        solve();

    return 0;
}