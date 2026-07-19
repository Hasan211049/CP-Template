#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Binary Trie (Bitwise Trie)

When to use:
1. Maximum XOR query.
2. Minimum XOR query.
3. Insert/Delete numbers dynamically.
4. Count numbers with certain XOR properties.
5. Offline XOR problems.
6. XOR basis related problems.

Idea:
Each number is stored bit by bit (from MSB to LSB).
Each node has at most two children:
0 -> bit 0
1 -> bit 1

This implementation supports:
- Insert
- Erase (duplicates allowed)
- Search
- Maximum XOR
- Minimum XOR

Time Complexity:
Insert      : O(LOG)
Erase       : O(LOG)
Search      : O(LOG)
Max XOR     : O(LOG)
Min XOR     : O(LOG)

LOG = 63 (for signed long long)

Space Complexity:
O(N * LOG)

Indexing: Not applicable.

Notes:
1. Supports duplicate numbers.
2. Root initially contains nothing.
3. Uses 63 bits (bit 62 ... bit 0).
4. Negative numbers are not recommended.
5. For normal competitive programming (numbers <= 1e18),
   this implementation is sufficient.

*/

struct BinaryTrie {

    static const int LOG = 62;

    struct Node {
        int child[2];
        int cnt;

        Node() {
            child[0] = child[1] = -1;
            cnt = 0;
        }
    };

    vector<Node> trie;

    BinaryTrie() {
        trie.emplace_back(); // root
    }

    // Insert number
    void insert(int x) {

        int node = 0;
        trie[node].cnt++;

        for (int b = LOG; b >= 0; b--) {

            int bit = (x >> b) & 1;

            if (trie[node].child[bit] == -1) {
                trie[node].child[bit] = trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[bit];
            trie[node].cnt++;
        }
    }

    // Search exact number
    bool search(int x) {

        int node = 0;

        for (int b = LOG; b >= 0; b--) {

            int bit = (x >> b) & 1;

            if (trie[node].child[bit] == -1)
                return false;

            node = trie[node].child[bit];

            if (trie[node].cnt == 0)
                return false;
        }

        return true;
    }

    // Erase one occurrence
    void erase(int x) {

        if (!search(x))
            return;

        int node = 0;
        trie[node].cnt--;

        for (int b = LOG; b >= 0; b--) {

            int bit = (x >> b) & 1;

            node = trie[node].child[bit];
            trie[node].cnt--;
        }
    }

    // Maximum XOR value with x
    int maxXor(int x) {

        if (trie[0].cnt == 0)
            return -1;

        int node = 0;
        int ans = 0;

        for (int b = LOG; b >= 0; b--) {

            int bit = (x >> b) & 1;
            int want = bit ^ 1;

            if (trie[node].child[want] != -1 &&
                trie[trie[node].child[want]].cnt > 0) {

                ans |= (1LL << b);
                node = trie[node].child[want];
            }
            else {
                node = trie[node].child[bit];
            }
        }

        return ans;
    }

    // Minimum XOR value with x
    int minXor(int x) {

        if (trie[0].cnt == 0)
            return -1;

        int node = 0;
        int ans = 0;

        for (int b = LOG; b >= 0; b--) {

            int bit = (x >> b) & 1;

            if (trie[node].child[bit] != -1 &&
                trie[trie[node].child[bit]].cnt > 0) {

                node = trie[node].child[bit];
            }
            else {

                ans |= (1LL << b);
                node = trie[node].child[bit ^ 1];
            }
        }

        return ans;
    }

};

void solve() {

    BinaryTrie bt;

    bt.insert(5);    // 101
    bt.insert(10);   // 1010
    bt.insert(7);    // 111

    cout << bt.search(5) << '\n';      // 1
    cout << bt.search(8) << '\n';      // 0

    cout << bt.maxXor(6) << '\n';
    // max(6^5,6^10,6^7)=12

    cout << bt.minXor(6) << '\n';
    // min(6^5,6^10,6^7)=1

    bt.erase(5);

    cout << bt.search(5) << '\n';      // 0
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