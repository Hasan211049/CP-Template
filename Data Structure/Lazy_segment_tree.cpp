#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Lazy Segment Tree (Range Add + Range Query)

When to use:
1. Range Update + Range Query.
2. Both update and query should be O(log N).

Idea:
Instead of immediately updating every element in a range,
store the pending update inside lazy[node].

Whenever that node is visited later,
propagate ("push") the pending update to its children.

Operations:
-----------
build()              -> O(N)
update(l,r,val)      -> O(log N)
query(l,r)           -> O(log N)

Complexity:
-----------
Build  : O(N)
Update : O(log N)
Query  : O(log N)
Memory : O(4N)

Indexing:
---------
1-based

Supported Operations:
---------------------------------------------------------
Query      Merge             Identity      Apply
---------------------------------------------------------
SUM        +                 0             += len * val
MAX        max()            -INF           += val
MIN        min()             INF           += val
---------------------------------------------------------

To change the operation,
ONLY modify these three functions:

1. merge()
2. identity()
3. apply()

*/

struct LazySegmentTree {

    int n;
    vector<int> tree, lazy;

    LazySegmentTree(int sz) {
        n = sz;
        tree.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    int merge(int left, int right) {

        return left + right;          // SUM

        // return max(left, right);   // MAX

        // return min(left, right);   // MIN
    }


    int identity() {

        return 0;          // SUM

        // return -INF;    // MAX

        // return INF;     // MIN
    }

   
    void apply(int node, int l, int r, int val) {

        // SUM
        // Every element increases by val.
        // Therefore total sum increases by
        // (segment length) * val.

        tree[node] += (r - l + 1) * val;

        // MAX / MIN
        // Every element increases equally.
        // Therefore maximum / minimum also increases by val.

        // tree[node] += val;


        // tree[node] += val;
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

   
    void push(int node, int l, int r) {

        if (lazy[node] == 0)
            return;

        apply(node, l, r, lazy[node]);

        if (l != r) {

            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, int val) {

        push(node, l, r);

        if (r < ql || l > qr)
            return;

        if (ql <= l && r <= qr) {

            lazy[node] += val;
            push(node, l, r);

            return;
        }

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);


        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int l, int r,
              int ql, int qr) {

        push(node, l, r);

        if (r < ql || l > qr)
            return identity();

        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    //================ Wrappers ================

    void build(vector<int> &a) {
        build(1, 1, n, a);
    }

    void update(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

void solve() {

    int n = 5;

    // 1-based array
    vector<int> a = {0, 2, 1, 5, 3, 4};

    LazySegmentTree st(n);

    st.build(a);

    cout << st.query(1, 5) << '\n';      // 15

    st.update(2, 4, 10);

    // Array becomes:
    // 2 11 15 13 4

    cout << st.query(1, 5) << '\n';      // 45
 
}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
        solve();

    return 0;
}