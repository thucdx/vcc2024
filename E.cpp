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

const int MAX_N = 3e5;
const ll INF = 1e15;

vector<pii> adj[MAX_N];
vector<ll> dist;
vector<pii> managedRanges;
map<int, int> leafId;
map<int, int> id2Ver;

/**
 * Find dist from each vertice to root.
 * Assign each leaf an id, and set a range of leaf id that is in subtree of each node.
 * - dist[i]: distance from i to root
 * - managedRanges[i]: start id of leaf and end id of leaf of which vertice i is parent
 */
pii dfs(int v, int par = -1) {
    int childCount = 0;
    int startRange = (int) 1e6, endRange = -1;

    EACH(nxt, adj[v]) {
        if (nxt.first != par) {
            childCount++;
            dist[nxt.first] = dist[v] + nxt.second;
            pii range = dfs(nxt.first, v);
            startRange = min(range.first, startRange);
            endRange = max(range.second, endRange);
        }
    }

    if (childCount == 0) {
       // insert new leaf
       int curLeafId = SZ(leafId) + 1;
       id2Ver[curLeafId] = v;
       leafId[v] = curLeafId;
       debug(v, curLeafId);
       startRange = curLeafId, endRange = curLeafId;
    }

    managedRanges[v] = {startRange, endRange};
    return managedRanges[v];
}


/**
 *  Segment tree with lazy propagation for 2 operations:
 *  given a_1, a_2, ... a_n
 * +    update: [l, r, newVal] => set all a_i (l <= i <= r) to newVal
 * +    get:     [l, r] => get minimum value of all a_i such that l <= i <= r
 */
ll segTree[4 * MAX_N];
bool marked[4 * MAX_N];

void push(int v) {
    if (marked[v]) {
        segTree[v*2] = segTree[v*2+1] = segTree[v];
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}

// update all value of in range [rangeStart, rangeEnd] with value `val`
void update(int v, int start, int end, int rangeStart, int rangeEnd, ll newVal) {
    if (rangeStart > rangeEnd) return;
    if (start == rangeStart && end == rangeEnd) {
        debug(v, start, end, newVal);
        segTree[v] = newVal;
        // lazy here
        marked[v] = true;
    } else {
        push(v);
        int mid = (start + end) / 2;
        update(2 * v, start, mid, rangeStart, min(mid, rangeEnd), newVal);
        update(2 * v + 1, mid + 1, end, max(mid + 1, rangeStart), rangeEnd, newVal);
        debug("update", v, segTree[2*v], segTree[2*v + 1]);
        segTree[v] = min(segTree[2*v], segTree[2*v + 1]);
    }
}

ll get(int v, int start, int end, int rangeStart, int rangeEnd) {
    if (start == rangeStart && end == rangeEnd) {
        debug("minRange", v, start, end);
        return segTree[v];
    }

    debug("minRange", start, end, rangeStart, rangeEnd);

    push(v);
    int tm = (start + end) / 2;
    ll left = get(2 * v, start, tm, rangeStart, min(tm, rangeEnd));
    ll right = get(2 * v + 1, tm + 1, end, max(tm + 1, rangeStart), rangeEnd);

    return min(left, right);
}

int main() {
#ifdef LOCAL
    freopen("inp/E1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    int v, c;
    FOR(i, 1, n-1) {
       cin >> v >> c;
       --v;
       adj[i].pb({v, c});
       adj[v].pb({i, c});
    }

    managedRanges.resize(n);
    dist.resize(n);
    memset(marked, false, sizeof(marked));

    dist[0] = 0;
    managedRanges[0] = dfs(0);
    debug(dist);

    REP(i, n) {
        debug(i, managedRanges[i]);
    }

    // build segment tree for all leaves
    int totalLeaves = SZ(leafId);
    FOR(i, 1, totalLeaves) {
        int ver = id2Ver[i];
        debug(i, ver, dist[ver]);
        update(1, 1, totalLeaves, i, i, dist[ver]);
    }

    // query
    REP(i, q) {
        cin >> v;
        v--;
        debug(v, managedRanges[v]);

        // Remove range managed by v
        update(1, 1, totalLeaves, managedRanges[v].first, managedRanges[v].second, INF);

        // Query
        ll minVal = get(1, 1, totalLeaves, 1, totalLeaves);
        debug(minVal);
        cout << (minVal == INF ? -1 : minVal) << endl;
    }
}