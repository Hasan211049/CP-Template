#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Euler Totient Sieve

Idea:
- Initially assume:
      phi[i] = i
- For every prime p:
      Every multiple of p loses 1/p of its value.
      phi[j] -= phi[j] / p

Time Complexity:
Build : O(N log log N); query : O(1);

Space Complexity: O(N)

*/

const int N = 1e6 + 5;

vector<int> phi(N);

void buildPhi() {

    for (int i = 0; i < N; i++)
        phi[i] = i;

    for (int i = 2; i < N; i++) {

        if (phi[i] == i) {          // i is prime

            for (int j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

void solve() {

    int n;
    cin >> n;

    cout << phi[n] << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    buildPhi();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}