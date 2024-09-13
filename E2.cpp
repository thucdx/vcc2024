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

struct Edge {
    int v, x;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector tree(n, vector<Edge>());
    vector<int> p(n);
    int c;
    FOR(i, 1, n-1) {
        cin >> p[i] >> c;
        --p[i];
        tree[p[i]].pb({i, c});
    }

    vector<ll> d(n);
    multiset<ll> s;

    function<void(int)> dfs1 = [&](int u) {
        if (tree[u].empty()) s.insert(d[u]);
        EACH(e, tree[u]) {
            d[e.v] = d[u] + e.x;
            dfs1(e.v);
        }
    };

    dfs1(0);

    vector<bool> blocked(n, false);

    function<void(int)> dfs2 = [&](int u) {
        if (blocked[u]) return;
        blocked[u] = true;
        if (tree[u].empty()) {
            s.erase(s.find(d[u]));
        }

        EACH(nxt, tree[u]) {
            dfs2(nxt.v);
        }
    };

    REP(i, q) {
        int x;
        cin >> x;
        x--;
        dfs2(x);
        ll ans = s.empty() ? -1 : *s.begin();
        cout << ans << endl;
    }
}


int main() {
#ifdef LOCAL
    freopen("inp/E1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}