#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Purpose:
- Finds all positive divisors of a number n.

Idea:
- Divisors always come in pairs.


So instead of checking from 1 to n,
we only check up to sqrt(n).


Time Complexity -> 

Loop: O(sqrt(n))

Sorting: O(d log d)

where d = number of divisors.

Overall: O(sqrt(n))

Space: O(d)

*/

vector<int> get_divisors(int n) {

    vector<int> divs;

    for (int i = 1; i * i <= n; i++) {

        if (n % i == 0) {

            divs.push_back(i);

            if (i != n / i)
                divs.push_back(n / i);
        }
    }

    sort(divs.begin(), divs.end());

    return divs;
}

void solve() {

    int n, k;
    cin >> n >> k; //It's actually finding k'th divisor of a single element

    vector<int> divs = get_divisors(n);

    for(int i: divs) cout<<i <<" ";
    cout<<endl;

    if (k > divs.size())
        cout << -1 << '\n';
    else
        cout << divs[k - 1] << '\n';
}

int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin>>t;

    while (t--)
        solve();

    return 0;
}