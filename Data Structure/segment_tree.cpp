#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Segment Tree (Range Query + Point Update)

When to use:
1. Multiple range queries.
2. Array values change during queries.
3. Prefix Sum is not enough because updates are required.
4. Both query and update should be O(log N).

Idea:

A Segment Tree is a binary tree where every node stores the answer
for a segment (interval) of the array.

Example:

Array:
Index : 1 2 3 4 5
Value : 2 1 5 3 4

Tree:

                    [1,5]
                  /       \
              [1,3]      [4,5]
             /    \      /    \
         [1,2]   [3]   [4]   [5]
         /   \
      [1]   [2]

Each node stores the answer of its interval.

For Sum:

[1,5] = 15
[1,3] = 8
[4,5] = 7

Range Query:
------------
Only visit nodes that intersect the query range.

Point Update:
-------------
Update one leaf, then recompute all its ancestors.

Operations:
-----------
build()          -> O(N)
query(l,r)       -> O(log N)
update(idx,val)  -> O(log N)

Complexity:
-----------
Build  : O(N)
Query  : O(log N)
Update : O(log N)
Memory : O(4N)

Indexing:
---------
1-based

Works for any associative operation.

---------------------------------------------------------
Operation     Merge                 Identity
---------------------------------------------------------
Sum           a+b                   0
Min           min(a,b)              INF
Max           max(a,b)             -INF
GCD           gcd(a,b)              0
XOR           a^b                   0
OR            a|b                   0
AND           a&b                  -1
LCM           lcm(a,b)              1 (watch overflow)
---------------------------------------------------------

To change the Segment Tree for another operation,
only modify TWO places:

1. merge()
2. identity()

*/

struct SegmentTree {

    int n;
    vector<int> tree;

    SegmentTree(int sz) {
        n = sz;
        tree.assign(4 * n + 5, 0);
    }

    // Merge Function
    // Change ONLY this function for another operation.
    int merge(int a, int b) {
        return a + b;
        // return min(a,b);
        // return max(a,b);
        // return __gcd(a,b);
        // return a ^ b;
        // return a | b;
        // return a & b;
        // return lcm(a,b);
    }

    // Identity Element
    // Change ONLY this function according to merge().
    int identity() {
        return 0;

        // Sum : 0
        // Min : INF
        // Max : -INF
        // GCD : 0
        // XOR : 0
        // OR  : 0
        // AND : -1
        // LCM : 1
    }

    void build(int node, int l, int r, vector<int> &a) {

        if (l == r) {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {

        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int l, int r, int ql, int qr) {

        // Completely outside
        if (r < ql || l > qr)
            return identity();

        // Completely inside
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    // Wrappers

    void build(vector<int> &a) {
        build(1, 1, n, a);
    }

    void update(int idx, int val) {
        update(1, 1, n, idx, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

void solve() {

    int n = 5;

    // 1-based array
    vector<int> a = {0, 2, 1, 5, 3, 4};

    SegmentTree st(n);

    st.build(a);

    cout << "Query [2,5] = " << st.query(2, 5) << '\n';

    st.update(3, 10);

    cout << "After Update\n";

    cout << "Query [2,5] = " << st.query(2, 5) << '\n';
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