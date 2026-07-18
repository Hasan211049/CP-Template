#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Merge Sort Tree (Static)

When to use:

1. Static array (No updates).
2. Count numbers <, <=, >, >= x in a range.
3. Count frequency of x in a range.
4. Binary Search on Answer problems.
5. Offline range order-statistics problems.

Indexing: 0-Based
Query Range: [l, r] (Inclusive)

Time Complexity:

Build              : O(N log N)
Each Query         : O(log²N)
Memory             : O(N log N)

Idea:

A Merge Sort Tree is a Segment Tree where every node stores
the sorted elements of its interval.

Leaf: Stores one element.

Internal Node:
Merge the sorted vectors of its two children.

Since every node is sorted,
binary_search() can answer counting queries.

Query visits O(logN) nodes.

Binary search on each node costs O(logN).

Overall:
O(log²N)

Supported Queries:

count < x
count <= x
count > x
count >= x
count == x

Notes:

• Static data structure.
• Does NOT support updates efficiently.
• Tree size = 4*N.
• Very useful for range counting problems.
• K-th smallest/largest requires Binary Search on Answer
  (or Persistent Segment Tree / Wavelet Tree).

*/

struct MergeSortTree {

    int n;
    vector<vector<int>> tree;

    MergeSortTree(vector<int> &a) {
        n = a.size();
        tree.resize(4 * n + 5);
        build(1, 0, n - 1, a);
    }

    void build(int node, int l, int r, vector<int> &a) {

        if (l == r) {
            tree[node] = {a[l]};
            return;
        }

        int mid = (l + r) >> 1;

        build(node << 1, l, mid, a);
        build(node << 1 | 1, mid + 1, r, a);

        merge(tree[node << 1].begin(), tree[node << 1].end(),
              tree[node << 1 | 1].begin(), tree[node << 1 | 1].end(),
              back_inserter(tree[node]));
    }

    // Count <= x

    int countLE(int node, int l, int r, int ql, int qr, int x) {

        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return upper_bound(tree[node].begin(), tree[node].end(), x)
                   - tree[node].begin();

        int mid = (l + r) >> 1;

        return countLE(node << 1, l, mid, ql, qr, x) +
               countLE(node << 1 | 1, mid + 1, r, ql, qr, x);
    }

    int countLE(int l, int r, int x) {
        return countLE(1, 0, n - 1, l, r, x);
    }

    // Count < x

    int countLT(int node, int l, int r, int ql, int qr, int x) {

        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return lower_bound(tree[node].begin(), tree[node].end(), x)
                   - tree[node].begin();

        int mid = (l + r) >> 1;

        return countLT(node << 1, l, mid, ql, qr, x) +
               countLT(node << 1 | 1, mid + 1, r, ql, qr, x);
    }

    int countLT(int l, int r, int x) {
        return countLT(1, 0, n - 1, l, r, x);
    }

    // Count >= x

    int countGE(int node, int l, int r, int ql, int qr, int x) {

        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return tree[node].size() -
                   (lower_bound(tree[node].begin(), tree[node].end(), x)
                    - tree[node].begin());

        int mid = (l + r) >> 1;

        return countGE(node << 1, l, mid, ql, qr, x) +
               countGE(node << 1 | 1, mid + 1, r, ql, qr, x);
    }

    int countGE(int l, int r, int x) {
        return countGE(1, 0, n - 1, l, r, x);
    }

    // Count > x

    int countGT(int node, int l, int r, int ql, int qr, int x) {

        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return tree[node].size() -
                   (upper_bound(tree[node].begin(), tree[node].end(), x)
                    - tree[node].begin());

        int mid = (l + r) >> 1;

        return countGT(node << 1, l, mid, ql, qr, x) +
               countGT(node << 1 | 1, mid + 1, r, ql, qr, x);
    }

    int countGT(int l, int r, int x) {
        return countGT(1, 0, n - 1, l, r, x);
    }

    // Count == x

    int countEQ(int node, int l, int r, int ql, int qr, int x) {

        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return upper_bound(tree[node].begin(), tree[node].end(), x) -
                   lower_bound(tree[node].begin(), tree[node].end(), x);

        int mid = (l + r) >> 1;

        return countEQ(node << 1, l, mid, ql, qr, x) +
               countEQ(node << 1 | 1, mid + 1, r, ql, qr, x);
    }

    int countEQ(int l, int r, int x) {
        return countEQ(1, 0, n - 1, l, r, x);
    }
};

void solve() {

    vector<int> a = {5, 1, 7, 3, 8, 2, 6};

    MergeSortTree mst(a);

    cout << "Count <= 5 : " << mst.countLE(1, 5, 5) << '\n';
    cout << "Count < 5  : " << mst.countLT(1, 5, 5) << '\n';
    cout << "Count >= 5 : " << mst.countGE(1, 5, 5) << '\n';
    cout << "Count > 5  : " << mst.countGT(1, 5, 5) << '\n';
    cout << "Count == 7 : " << mst.countEQ(1, 5, 7) << '\n';
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--) solve();

    return 0;
}