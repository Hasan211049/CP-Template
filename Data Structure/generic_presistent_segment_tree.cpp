#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Generic Persistent Segment Tree

Index: 1-based

Supports:
1. Build initial version
2. Point Update (creates a new version)
3. Range Query on any version

Default Operation: Range Sum

To change the operation:
1. Modify merge()
2. Modify DEFAULT value if necessary.

Complexity:
Build   : O(N)
Update  : O(log N)
Query   : O(log N)

Memory:
Build   : O(N)
Each Update : O(log N)

Advantages:
1. Every update creates a new version.
2. Old versions remain unchanged.
3. Supports time-travel queries.
4. Ideal for offline queries.

*/

struct PersistentSegmentTree {

    struct Node {
        int val;
        int left, right;

        Node(int v = 0, int l = 0, int r = 0) {
            val = v;
            left = l;
            right = r;
        }
    };

    vector<Node> tree;
    vector<int> root; //version store kore
    int n;

    PersistentSegmentTree(int sz) {
        n = sz;
        tree.reserve(20 * n);
        tree.push_back(Node()); // dummy node (index 0)
    }

    // Change ONLY this function

    int merge(int a, int b) {

        return a + b;

        // return min(a, b);

        // return max(a, b);

        // return gcd(a, b);

        // return (a ^ b);

        // return (a | b);

        // return (a & b);
    }

    int identity() {

        return 0;

        // return INF;        // min

        // return -INF;       // max

        // return 0;          // gcd

        // return 0;          // xor

        // return 0;          // or

        // return ~0LL;         // and (all bits = 1)
    }

    int apply(int oldValue, int updateValue) {

        return updateValue;             // Assignment

        // return oldValue + updateValue;   // Add

        // return oldValue ^ updateValue;   // XOR

        // return oldValue | updateValue;   // OR

        // return oldValue & updateValue;   // AND

        // return max(oldValue, updateValue); //MAX

        // return min(oldValue, updateValue); //MIN
    }

    int build(const vector<int> &a, int l, int r) {

        int node = tree.size();
        tree.push_back(Node());

        if (l == r) {
            tree[node].val = a[l];
            return node;
        }

        int mid = (l + r) >> 1;

        tree[node].left = build(a, l, mid);
        tree[node].right = build(a, mid + 1, r);

        tree[node].val = merge(tree[tree[node].left].val,
                               tree[tree[node].right].val);

        return node;
    }

    void build(vector<int> &a) {

        root.clear();
        root.push_back(build(a, 1, n));
    }

    int update(int prev, int l, int r, int idx, int val) {

        int node = tree.size();
        Node node_copy = tree[prev];
        tree.push_back(node_copy);

        if (l == r) {
            tree[node].val = apply(tree[prev].val, val);
            return node;
        }
    
        int mid = (l + r) >> 1;

        if (idx <= mid)
            tree[node].left = update(tree[prev].left, l, mid, idx, val);
        else
            tree[node].right = update(tree[prev].right, mid + 1, r, idx, val);

        tree[node].val = merge(tree[tree[node].left].val,
                               tree[tree[node].right].val);

        return node;
    }

    void update(int version, int idx, int val) {

        root.push_back(update(root[version], 1, n, idx, val));
    }

    int query(int node, int l, int r, int ql, int qr) {

        if (qr < l || r < ql)
          return identity(); 

        if (ql <= l && r <= qr)
            return tree[node].val;

        int mid = (l + r) >> 1;

        return merge(query(tree[node].left, l, mid, ql, qr),
                     query(tree[node].right, mid + 1, r, ql, qr));
    }

    int query(int version, int l, int r) {

        return query(root[version], 1, n, l, r);
    }

    int versions() {
        return root.size();
    }
};

void solve() {

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    PersistentSegmentTree pst(n);

    pst.build(a);               // Version 0

    while (q--) {

        int type; //indicate's what type of operation have to be performed !

        cin >> type;

        // 1 -> update

        if (type == 1) {

            int version, idx, val;
            cin >> version >> idx >> val;

            pst.update(version, idx, val);

            cout << "Created Version " << pst.versions() - 1 << '\n';
        }

        // 2 -> query version l r
        else {

            int version, l, r;
            cin >> version >> l >> r;

            cout << pst.query(version, l, r) << '\n';
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