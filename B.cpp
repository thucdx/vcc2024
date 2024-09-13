#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL

#include <algo/debug.h>

#else
#define debug(...) void(31)
#endif

#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define REP(i, n) for (int i = 0; i < (int)n; ++i)
#define FOR(i, a, b) for (int i = (int)a; i <= (int)b; ++i)
#define FORD(i, b, a) for (int i = (int)b; i >= (int)a; --i)
#define EACH(v, a) for (auto& v : a)
#define SZ(a) ((int) a.size())

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int>>;


int main() {
#ifdef LOCAL
    freopen("inp/B3.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    const int INF = (int) 1e6 + 5;
    vi val(n + 2, -1);
    map<int, int> after;
    map<int, int> before;
    map<int, int> pos;
    set<int> all;
    int u, v;
    REP(i, n) {
        cin >> u >> v;
        if (v == 0) {
            v = INF;
        }
        after[u] = v;
        before[v] = u;
        all.insert(u);
        all.insert(v);
        debug(u, v);
    }

    // start
    int lastFound = -1;
    int curP = 0, curV = 0;
    while (curP <= n) {
        all.erase(curV);
        pos[curV] = curP;
        val[curP] = curV;
        lastFound = curV;
        debug(curP, curV);
        curV = after[curV];
        curP += 2;
        debug("after", curV, curP);
    }
    debug(val);
    debug(lastFound);

    // end
    if (n % 2 == 0) {
        curP = n + 1, curV = INF;
        while (curP >= 0) {
            val[curP] = curV;
            debug(curP, curV);
            curV = before[curV];
            curP -= 2;
        }
        debug(val);
    } else {
        // n % 2 == 1
        // no after
        int last = -INF;
        EACH(v, all) {
            debug(v);
            if (v != INF && after.count(v) == 0) {
                last = v;
//                debug(last);
            }
        }
        debug(last);
        curP = n, curV = last;
        while (curP >= 0) {
            val[curP] = curV;
            debug(curP, curV);
            curV = before[curV];
            curP -= 2;
        }
    }

    FOR(i, 1, n) {
        cout << val[i] << " ";
    }
    cout << endl;
}