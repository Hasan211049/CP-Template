#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int mod = 1e9 + 7;

const int N = 1005;

int a[N][N];
int pref[N][N];

/*Explanation :

Purpose:
- Find the sum of any sub-rectangle of a matrix in O(1).

Idea:
- Precompute prefix sums.

pref[i][j] stores:

Sum of all elements inside rectangle:

(1,1) -> (i,j)


Formula:

pref[i][j]
=
a[i][j]
+ pref[i-1][j]
+ pref[i][j-1]
- pref[i-1][j-1]


Why subtract?

Because the top-left rectangle
(pref[i-1][j-1])
was counted twice.



Query:

Find sum of rectangle: (x1,y1) -> (x2,y2)


Formula:

answer =

pref[x2][y2]

- pref[x1-1][y2]

- pref[x2][y1-1]

+ pref[x1-1][y1-1]


Reason:

Take full rectangle,
remove extra top part,
remove extra left part,
add back overlapping corner.



Complexity:

Building prefix:
O(n*m)

Each query:
O(1)

Memory:
O(n*m)



Notes:

- Use 1-indexing to avoid boundary problems.
- pref[0][*] and pref[*][0] remain zero.
- For large values use long long.

*/

void solve() {

    int n, m;
    cin >> n >> m; 

    //Used 1'base index


    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            cin >> a[i][j];
        }
    }


    // Build prefix sum

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            pref[i][j] =
                pref[i-1][j]
                + pref[i][j-1]
                - pref[i-1][j-1]
                + a[i][j];
        }
    }


    int q;
    cin >> q;


    while(q--) {

        int x1, y1, x2, y2;

        cin >> x1 >> y1 >> x2 >> y2;


        int ans =
            pref[x2][y2]
            - pref[x1-1][y2]
            - pref[x2][y1-1]
            + pref[x1-1][y1-1];


        cout << ans << '\n';
    }
}


int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t = 1;

    while(t--)
        solve();


    return 0;
}