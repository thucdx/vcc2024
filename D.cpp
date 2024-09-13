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
    freopen("inp/D3.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nTest;
    cin >> nTest;
    REP(_, nTest) {
        int n;
        cin >> n;
        vi l(n), r(n);
        l.clear(), r.clear();
        vector<pii> heads;
        set<pii> ranges;
        map<int, int> hei;
        REP(i, n) {
            cin >> l[i] >> r[i];
            debug(l[i], r[i]);
            ranges.insert({l[i], r[i]});
            // 0 -> begin, 1 -> end;
            heads.pb({l[i], 0});
            heads.pb({r[i], 1});
        }

        sort(all(heads));
        debug(heads);

        int open = 0, openAndClose = 0;
        int lastVal = -1;
        EACH(head, heads) {
            if (head.first != lastVal && lastVal != -1) {
                hei.insert({lastVal, openAndClose});
                // reset
                openAndClose = open;
            }

            lastVal = head.first;

            // still at lastVal
            if (head.second == 0) {
                openAndClose++;
            }
            if  (head.second == 1) {
                // close
                open--;
            } else {
                // open
                open++;
            };
        }

        if (lastVal != -1) {
            hei.insert({lastVal, openAndClose});
        }

        int maxQ = 0;
        vector<int> maxNodes;

        EACH(h, hei) {
            debug(h);
            if (h.second > maxQ) {
                maxQ = h.second;
                maxNodes.clear();
                maxNodes.pb(h.first);
            } else if (h.second == maxQ) {
                maxNodes.pb(h.first);
            }
        }

        debug(maxNodes.size(), maxNodes);

        int sz = SZ(maxNodes);
        if (sz == 1) {
            maxQ--;
        } else if (sz >= 2) {
            int first = maxNodes[0], second = maxNodes[sz - 1];
            if (first > second) {
                swap(first, second);
            }

            bool ok = false;
            EACH(range, ranges) {
                if (range.first <= first && range.second >= second) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                maxQ--;
            }
        }

        cout << maxQ << endl;
        debug("================");

        debug(maxQ);
    }
}