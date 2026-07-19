#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Chairman Tree (Persistent Segment Tree)

N.B : we can perform any operation on previous versions

Index: Array : 1-based

Supports:
---------
1. Build from array
2. Count numbers < x in [l,r]
3. Count numbers <= x in [l,r]
4. Count numbers > x in [l,r]
5. Count numbers >= x in [l,r]
6. k-th smallest in [l,r]
7. k-th largest in [l,r]

Idea:
-----
root[i] stores frequency of first i elements.

Query on [l,r] =
root[r] - root[l-1]

Complexity:
-----------
Build      : O(N log N)
Each Query : O(log N)

Memory:
--------
O(N log N)

Requires Coordinate Compression.

*/

struct ChairmanTree {

    struct Node {
        int left = 0;
        int right = 0;
        int sum = 0;
    };

    vector<Node> tree;
    vector<int> root;
    vector<int> value;

    int SZ;

    ChairmanTree() {
        tree.push_back(Node()); // dummy node
    }

    int clone(int node) {
        tree.push_back(tree[node]);
        return (int)tree.size() - 1;
    }

    int update(int prev, int l, int r, int pos) {

        int cur = clone(prev);
        tree[cur].sum++;

        if (l != r) {

            int mid = (l + r) >> 1;

            if (pos <= mid)
                tree[cur].left = update(tree[prev].left, l, mid, pos);
            else
                tree[cur].right = update(tree[prev].right, mid + 1, r, pos);
        }

        return cur;
    }

    void build(vector<int> &a) {

        int n = (int)a.size() - 1;

        value.clear();

        for (int i = 1; i <= n; i++)
            value.push_back(a[i]);

        sort(value.begin(), value.end());
        value.erase(unique(value.begin(), value.end()), value.end());

        SZ = value.size();

        root.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            int pos = lower_bound(value.begin(), value.end(), a[i]) - value.begin() + 1;

            root[i] = update(root[i - 1], 1, SZ, pos);
        }
    }

    int queryCount(int u, int v, int l, int r, int ql, int qr) {

        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return tree[v].sum - tree[u].sum;

        int mid = (l + r) >> 1;

        return queryCount(tree[u].left, tree[v].left, l, mid, ql, qr)
             + queryCount(tree[u].right, tree[v].right, mid + 1, r, ql, qr);
    }

    //----------------------------------
    // count < x
    //----------------------------------

    int countLess(int l, int r, int x) {

        int pos = lower_bound(value.begin(), value.end(), x) - value.begin();

        if (pos == 0) return 0;

        return queryCount(root[l - 1], root[r], 1, SZ, 1, pos);
    }

    //----------------------------------
    // count <= x
    //----------------------------------

    int countLessEqual(int l, int r, int x) {

        int pos = upper_bound(value.begin(), value.end(), x) - value.begin();

        if (pos == 0) return 0;

        return queryCount(root[l - 1], root[r], 1, SZ, 1, pos);
    }

    //----------------------------------
    // count > x
    //----------------------------------

    int countGreater(int l, int r, int x) {

        return (r - l + 1) - countLessEqual(l, r, x);
    }

    //----------------------------------
    // count >= x
    //----------------------------------

    int countGreaterEqual(int l, int r, int x) {

        return (r - l + 1) - countLess(l, r, x);
    }

    //----------------------------------
    // kth smallest (1-based)
    //----------------------------------

    int kth(int u, int v, int l, int r, int k) {

        if (l == r)
            return l;

        int mid = (l + r) >> 1;

        int cnt = tree[tree[v].left].sum - tree[tree[u].left].sum;

        if (k <= cnt)
            return kth(tree[u].left, tree[v].left, l, mid, k);

        return kth(tree[u].right, tree[v].right, mid + 1, r, k - cnt);
    }

    int kthSmallest(int l, int r, int k) {

        int idx = kth(root[l - 1], root[r], 1, SZ, k);

        return value[idx - 1];
    }

    //----------------------------------
    // kth largest (1-based)
    //----------------------------------

    int kthLargest(int l, int r, int k) {

        int len = r - l + 1;

        return kthSmallest(l, r, len - k + 1);
    }

};

void solve() {

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    ChairmanTree CT;
    CT.build(a);

    while (q--) {

        int type;
        cin >> type;

        if (type == 1) {

            int l, r, x;
            cin >> l >> r >> x;

            cout << CT.countLess(l, r, x) << '\n';
        }

        else if (type == 2) {

            int l, r, x;
            cin >> l >> r >> x;

            cout << CT.countLessEqual(l, r, x) << '\n';
        }

        else if (type == 3) {

            int l, r, x;
            cin >> l >> r >> x;

            cout << CT.countGreater(l, r, x) << '\n';
        }

        else if (type == 4) {

            int l, r, x;
            cin >> l >> r >> x;

            cout << CT.countGreaterEqual(l, r, x) << '\n';
        }

        else if (type == 5) {

            int l, r, k;
            cin >> l >> r >> k;

            cout << CT.kthSmallest(l, r, k) << '\n';
        }

        else {

            int l, r, k;
            cin >> l >> r >> k;

            cout << CT.kthLargest(l, r, k) << '\n';
        }
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