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

// Find x such that (arr_0 - x) XOR (arr_1 - x) XOR ... XOR (arr_k - x) equals to target
ll find(vector<ll> arr, ll target) {
    debug(arr, target);
    ll res = 0;
    REP(i, 63) {
        ll bit = target >> i & 1;
        EACH(val, arr) {
            bit ^= val >> i & 1;
        }

        assert(bit <= 1);
        if (bit) {
            res += 1LL << i;
            EACH(val, arr) {
                // move from right to left,
                // to ensure that when we substract 2^i on val, it affects only on left bits,
                // and not touch already procressed bits (right bits)
                val -= (1LL << i);
                if (val < 0) {
                    return -1;
                }
            }
        }
    }

    return res;
}

void solve(vector<long long> arr) {
    int sz = SZ(arr);
    vector<vector<ll>> res;
    ll allXOR = 0;
    EACH(val, arr) allXOR ^= val;

    REP(l, sz) {
        ll target = allXOR;
        FOR(r, l, sz) {
            target ^= arr[r];
            // range [l, r] length should be odd
            if ((r - l + 1) % 2 == 0) continue;
            ll x = find(vector<ll>(arr.begin() + l, arr.begin() + r + 1), target);
            debug(l, r, x);
            if (x > 0) {
                // Solution found
                vector<ll> sol(sz, 0);
                FOR(i, l, r) sol[i] = x;
                res.pb(sol);
            }
        }
    }

    // Sort in alphabet order
    sort(all(res));

    // Print all
    cout << SZ(res) << endl;
    EACH(sol, res) {
        EACH(v, sol) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("inp/H2.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> f;
    ll val;
    REP(i, 5) {
        cin >> val;
        f.pb(val);
    }

    solve(f);
}
