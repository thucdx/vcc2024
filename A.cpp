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
    freopen("inp/A1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> x(n), y(n), t(n);
    ll curX = 0, curY = 0, curT = 0;

    bool isOK = true;
    REP(i, n) {
        cin >> x[i] >> y[i] >> t[i];
        ll d = abs(x[i] - curX) + abs(y[i] - curY);
        ll distT = t[i] - curT;
        if (distT < d) {
            isOK = false;
            break;
        }

        // distT >= d
        curX = x[i];
        curY = y[i];
        curT = t[i];
        debug(curX, curY, curT);
    }

    cout << (isOK ? "YES" : "NO") << endl;


}