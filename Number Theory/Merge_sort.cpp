#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

/*Explanation :

Purpose:
- Sorts an array using Merge Sort.



Merge Sort follows:

Divide:
    Split array into two halves.

Conquer:
    Sort both halves recursively.

Combine:
    Merge two sorted arrays.


Algorithm:

merge():

1. Take two sorted arrays.
2. Compare their first elements.
3. Put smaller element into answer.
4. Continue until one array ends.
5. Add remaining elements.

merge_sort() / divide:

1. If only one element, return it.
2. Find middle point.
3. Sort left half.
4. Sort right half.
5. Merge both halves.



Time Complexity:

Each level: O(n)

Number of levels: O(log n)

Total: O(n log n)

Space Complexity: O(n)

because temporary vectors are created during merging.



Best/Average/Worst:
O(n log n)


Uses:
- Inversion counting
- Divide and conquer
- Counting smaller elements
- External sorting


*/

vector<int> a;


vector<int> merge(vector<int> &l, vector<int> &r) {

    int n = l.size();
    int m = r.size();

    vector<int> ans;

    int i = 0;
    int j = 0;


    while (i < n && j < m) {

        if (l[i] <= r[j])
            ans.push_back(l[i++]);

        else
            ans.push_back(r[j++]);
    }


    while (i < n)
        ans.push_back(l[i++]);


    while (j < m)
        ans.push_back(r[j++]);


    return ans;
}


vector<int> merge_sort(int l, int r) {

    if (l == r)
        return {a[l]};


    int mid = l + (r - l) / 2;


    vector<int> left = merge_sort(l, mid);

    vector<int> right = merge_sort(mid + 1, r);


    return merge(left, right);
}


void solve() {

    int n;
    cin >> n;

    a.resize(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];


    vector<int> ans = merge_sort(0, n - 1);


    for (auto x : ans)
        cout << x << ' ';

    cout << '\n';
}


int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t = 1;
  //  cin>>t;

    while (t--)
        solve();


    return 0;
}