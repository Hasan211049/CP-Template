#include <bits/stdc++.h>
using namespace std;

#define int long long

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic: Policy Based Data Structure (PBDS) - Ordered Set

Indexing: 0-based 
(find_by_order(k) returns the k-th element where k starts from 0)

When to use:
1. K-th smallest element.
2. Rank of an element.
3. Insert/Delete/Search in O(log N).
4. Order Statistics.
5. Dynamic sorted set.

Idea: PBDS is a balanced BST (Red-Black Tree) with extra order statistics.

Special Operations:
order_of_key(x)        -> Number of elements strictly smaller than x
find_by_order(k)       -> Iterator to k-th smallest (0-based)


Time Complexity:
Insert      : O(log N)
Erase       : O(log N)
Find        : O(log N)
order_of_key: O(log N)
find_by_order: O(log N)

Memory: O(N)



PBDS stores UNIQUE elements only.

*/

template<typename T>
using ordered_set =
tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

void solve() {

    ordered_set<int> os;

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