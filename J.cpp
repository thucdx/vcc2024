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
#define SZ(a) ((int)a.size())

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int> >;

const int MOD = 998244353;

int power(int x, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = (1LL * res * x) % MOD;
        x = (1LL * x * x) % MOD;
        n >>= 1;
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> fac(n + 1, 1), revFac(n + 1, 1);
    FOR(i, 1, n) {
        fac[i] = i * fac[i - 1];
        // revFac[i] =  is inverse of i!, i.e revFac[i] * fac[i] = 1 (mod MOD)
        // we know that t^(p-1) = 1 (mod p) for all 0 < t < p
        // so => inv(t) = t^(p-2) (mod p)
        // => revFac[i] = inv(i!) = fac(i)^(p-2)
        revFac[i] = power(fac[i], MOD - 2);
    }

    // C(n, k): number of way to select k element out of n.
    // C(n, k) = n! / (k! * (n-k)!) = n! * inv(k!) * inv((n-k)!);
    auto C = [&](int n, int k) -> int {
        if (k > n) return 0;
        return fac[n] * revFac[k] % MOD * revFac[n - k] % MOD;
    };

    vvi adj(n);
    REP(i, n - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vi dist(n, 0);

    auto dfs = [&](auto self, int u, int p = -1) -> void {
        EACH(v, adj[u]) {
            if (v != p) {
                dist[v] = dist[u] + 1;
                self(self, v, u);
            }
        }
    };

    ll ans = 0;
    REP(i, n) {
        dist[i] = 0;
        dfs(dfs, i, -1);
        REP(j, n) {
            debug(k, n - 1 - dist[j], C(n - 1 - dist[j], k));
            ans = (ans + C(n - 1 - dist[j], k)) % MOD;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("inp/J2.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
