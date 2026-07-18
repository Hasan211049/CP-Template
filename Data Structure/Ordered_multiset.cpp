#include <bits/stdc++.h>
using namespace std;

#define int long long

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Ordered Multiset (PBDS)

Indexing: 0-based

When to use:
1. Duplicate elements are allowed.
2. K-th smallest/largest element.
3. Find rank of an element.
4. Dynamic ordered statistics.
5. Sliding Window Median.
6. Inversion Count.
7. Maintain sorted multiset.

Idea:
PBDS does not support duplicates.

Store each element as:
(value, unique_id)

Since every unique_id is different,
duplicate values become unique pairs.

Operations:

insert(x)
erase(x)               // erase one occurrence
count(x)
contains(x)

* find_by_order(k)       // k-th smallest (0-based)

* order_of_key(x)  = count of elements < x

o* rder_of_key_equal(x) = count of elements <= x

smallest()
largest()

lower_bound(x)
upper_bound(x)

Time Complexity:

Insert      O(log N)
Erase       O(log N)
Find        O(log N)
Rank        O(log N)
K-th        O(log N)

Memory:
O(N)

*/

template<typename T>
using pbds =
tree<
    pair<T,int>,
    null_type,
    less<pair<T,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

template<typename T>
struct OrderedMultiset {

    pbds<T> tree;
    int id = 0;

    // Insert one occurrence
    void insert(T x) {
        tree.insert({x, id++});
    }

    // Erase one occurrence
    bool erase(T x) {
        auto it = tree.lower_bound({x, 0});

        if (it == tree.end() || it->first != x)
            return false;

        tree.erase(it);
        return true;
    }

    // Number of occurrences of x
    int count(T x) {
        return tree.order_of_key({x, INT_MAX})
             - tree.order_of_key({x, 0});
    }

    // Check existence
    bool contains(T x) {
        auto it = tree.lower_bound({x, 0});
        return (it != tree.end() && it->first == x);
    }

    // Number of elements strictly smaller than x
    int order_of_key(T x) {
        return tree.order_of_key({x, 0});
    }

    // Number of elements <= x
    int order_of_key_equal(T x) {
        return tree.order_of_key({x, INT_MAX});
    }

    // k-th smallest (0-based)
    T find_by_order(int k) {
        return tree.find_by_order(k)->first;
    }

    // Smallest element
    T smallest() {
        return tree.begin()->first;
    }

    // Largest element
    T largest() {
        return tree.find_by_order(tree.size()-1)->first;
    }

    int size() {
        return tree.size();
    }

    bool empty() {
        return tree.empty();
    }

    void clear() {
        tree.clear();
        id = 0;
    }
};

void solve() {

    OrderedMultiset<int> ms;

    ms.insert(5);
    ms.insert(5);
    ms.insert(10);
    ms.insert(7);
    ms.insert(1);
    ms.insert(7);

    // 1 5 5 7 7 10

    cout << "Size = " << ms.size() << '\n';

    cout << "Smallest = "
         << ms.smallest() << '\n';

    cout << "Largest = "
         << ms.largest() << '\n';

    cout << "0-th smallest = "
         << ms.find_by_order(0) << '\n';

    cout << "3-rd smallest = "
         << ms.find_by_order(3) << '\n';

    cout << "Elements < 7 = "
         << ms.order_of_key(7) << '\n';

    cout << "Elements <= 7 = "
         << ms.order_of_key_equal(7) << '\n';

    cout << "Count of 5 = "
         << ms.count(5) << '\n';

    cout << "Contains 10 = "
         << ms.contains(10) << '\n';

    ms.erase(5);

    cout << "\nAfter deleting one 5:\n";

    while (!ms.empty()) {
        cout << ms.smallest() << ' ';
        ms.erase(ms.smallest());
    }
    cout << '\n';
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