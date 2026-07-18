#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Topic:
Trie (Prefix Tree)

When to use:
1. Fast insertion and searching of strings.
2. Prefix searching.
3. Counting words with a given prefix.
4. Dictionary problems.
5. Auto-complete.
6. Lexicographical traversal.
7. Maximum XOR problems (Binary Trie variant).

Idea:
Each node represents a prefix.
Each edge represents one character ('a' ~ 'z').

Example:

Insert:
cat
car
dog

(root)
 ├── c
 │    └── a
 │         ├── t (cat)
 │         └── r (car)
 └── d
      └── o
           └── g (dog)

Every node stores:
1. next[26] -> children
2. cntPrefix -> number of words passing this node
3. cntEnd -> number of words ending here

Operations:
insert(word)
erase(word)
search(word)
startsWith(prefix)
countEqual(word)
countPrefix(prefix)

Time Complexity:
Insert         : O(L)
Erase          : O(L)
Search         : O(L)
Prefix Search  : O(L)

L = length of string

Space Complexity:
O(total characters inserted)

Indexing:
0-based nodes.
Root = node 0.

Advantages:
✔ Very fast.
✔ Prefix queries.
✔ Easy to extend.

Limitations:
✘ Uses more memory than map/set.
✘ Alphabet size affects memory.

Common Mistakes:
1. Forgetting to increase prefix count.
2. Forgetting to decrease prefix count while erase.
3. Erasing non-existing strings.
4. Forgetting cntEnd for duplicate words.
*/

struct Trie {

    struct Node {
        int nxt[26];
        int cntPrefix;
        int cntEnd;

        Node() {
            memset(nxt, -1, sizeof(nxt));
            cntPrefix = 0;
            cntEnd = 0;
        }
    };

    vector<Node> trie;

    Trie() {
        trie.push_back(Node()); // root
    }

    // Insert word
    void insert(string s) {
        int node = 0;

        for(char c : s) {
            int id = c - 'a';

            if(trie[node].nxt[id] == -1) {
                trie[node].nxt[id] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].nxt[id];
            trie[node].cntPrefix++;
        }

        trie[node].cntEnd++;
    }

    // Search exact word
    bool search(string s) {
        int node = 0;

        for(char c : s) {
            int id = c - 'a';

            if(trie[node].nxt[id] == -1)
                return false;

            node = trie[node].nxt[id];
        }

        return trie[node].cntEnd > 0;
    }

    // Prefix exists?
    bool startsWith(string s) {
        int node = 0;

        for(char c : s) {
            int id = c - 'a';

            if(trie[node].nxt[id] == -1)
                return false;

            node = trie[node].nxt[id];
        }

        return true;
    }

    // Count exact word
    int countEqual(string s) {
        int node = 0;

        for(char c : s) {
            int id = c - 'a';

            if(trie[node].nxt[id] == -1)
                return 0;

            node = trie[node].nxt[id];
        }

        return trie[node].cntEnd;
    }

    // Count words having given prefix
    int countPrefix(string s) {
        int node = 0;

        for(char c : s) {
            int id = c - 'a';

            if(trie[node].nxt[id] == -1)
                return 0;

            node = trie[node].nxt[id];
        }

        return trie[node].cntPrefix;
    }

    // Erase one occurrence
    bool erase(string s) {

        if(!search(s))
            return false;

        int node = 0;

        for(char c : s) {
            int id = c - 'a';
            node = trie[node].nxt[id];
            trie[node].cntPrefix--;
        }

        trie[node].cntEnd--;

        return true;
    }

};

void solve() {

    Trie T;

    T.insert("cat");
    T.insert("car");
    T.insert("cat");
    T.insert("dog");

    cout << T.search("cat") << '\n';        // 1
    cout << T.search("cow") << '\n';        // 0

    cout << T.startsWith("ca") << '\n';     // 1
    cout << T.startsWith("do") << '\n';     // 1
    cout << T.startsWith("co") << '\n';     // 0

    cout << T.countEqual("cat") << '\n';    // 2
    cout << T.countEqual("car") << '\n';    // 1

    cout << T.countPrefix("ca") << '\n';    // 3
    cout << T.countPrefix("do") << '\n';    // 1

    T.erase("cat");

    cout << T.countEqual("cat") << '\n';    // 1
    cout << T.countPrefix("ca") << '\n';    // 2
}

int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while(t--)
        solve();

    return 0;
}