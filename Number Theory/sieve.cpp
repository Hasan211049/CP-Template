#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Sieve of Eratosthenes

Idea:
- Initially assume every number is prime.
- Start from 2.
- If i is prime, mark all multiples of i (starting from i*i) as composite.
- Starting from i*i is enough because smaller multiples have already been marked.

Time Complexity:
O(n log log n)

Space Complexity:
O(n)

*/

const int N = 1e6 + 5;

vector<bool> isPrime(N, true);
vector<int> primes; //store all prime

void sieve() {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i < N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < N; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 2; i < N; i++)
        if (isPrime[i]) primes.push_back(i);
}

void solve() {
    int n;
    cin >> n;

    if (isPrime[n])
        cout << "Prime\n";
    else
        cout << "Not Prime\n";
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sieve();

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}