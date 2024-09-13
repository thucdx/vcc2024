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
    freopen("inp/G1.in", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int nTest;
    cin >> nTest;
    debug(nTest);
    REP(_, nTest) {
        int m, n;
        cin >> m >> n;
        vi a(m), b(n);
        REP(i, m) cin >> a[i];
        REP(i, n) cin >> b[i];
        map<int, int> fA, fB;
        EACH(ai, a) fA[ai]++;
        EACH(bi, b) fB[bi]++;

        map<pii, int> cnt;
        EACH(ai, fA) EACH(bi, fB) {
            int freq = min(ai.second, bi.second);
            int g = gcd(ai.first, bi.first);
            int fa = ai.first / g, fb = bi.first / g;
            cnt[{fa, fb}] += freq;
        }

        int maxFreq = 0;
        EACH(v, cnt) {
            maxFreq = max(maxFreq, v.second);
        }
        cout << (n + m - maxFreq) << endl;
    }
}
