#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Sparse Table (Generic)

When to use:
1. Static Array (No Updates).
2. Fast Range Queries.
3. Idempotent Operations.

Supported Operations:
✓ Minimum
✓ Maximum
✓ GCD
✓ Bitwise AND
✓ Bitwise OR

Not Supported:
✗ Sum -> But can be possible using different type query (TC : logn)
✗ XOR -> Not Idempotent
✗ Product -> 0 issue
✗ Point Update
✗ Range Update

Time Complexity:
Build : O(N log N)
Query : O(1)

Space Complexity:
O(N log N)

Indexing: 1-Based

How to change operation?
Modify ONLY the merge() function.

Examples:

return min(a, b);
return max(a, b);
return gcd(a, b);
return (a & b);
return (a | b);

*/

struct SparseTable {

    int n, LOG;
    vector<vector<int>> st;
    vector<int> lg;

    int merge(int a, int b) { //you can change here !

        return min(a, b);

        // return max(a, b);

        // return gcd(a, b);

        // return (a & b);

        // return (a | b);
    }

    void build(vector<int> &a) {

        n = (int)a.size() - 1;

        LOG = __lg(n) + 1;

        st.assign(LOG, vector<int>(n + 1));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;

        for (int i = 1; i <= n; i++)
            st[0][i] = a[i];

        for (int k = 1; k < LOG; k++) {

            int len = 1LL << k;

            for (int i = 1; i + len - 1 <= n; i++) {

                st[k][i] = merge(
                    st[k - 1][i],
                    st[k - 1][i + (len >> 1)]
                );
            }
        }
    }

    int query(int l, int r) {

        int k = lg[r - l + 1];

        return merge(
            st[k][l],
            st[k][r - (1LL << k) + 1]
        );
    }

};

void solve() {

    int n;
    cin >> n;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SparseTable ST;
    ST.build(a);

    int q;
    cin >> q;

    while (q--) {

        int l, r;
        cin >> l >> r;

        cout << ST.query(l, r) << '\n';
    }

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