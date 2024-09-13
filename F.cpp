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
using vvi = vector<vector<int> >;

const int INF = 1e8;

struct Trie {
    Trie *child[2] = {};
    int minAccept = INF;
    int minDeny = INF;
};

// A -> accept = true, D -> accept = false;
// node a.b.c.d has state = a * 256^3 + b * 256^2 + c * 256 + d
void update(Trie *root, bool accept, ll state, int bit, int queryId) {
    debug("update", accept, state, bit, queryId);
    Trie *cur = root;
    for (int i = 1; i <= bit; i++) {
        // left or right
        bool bitI = (state >> (32 - i)) & 1;

        if (cur->child[bitI] == NULL) {
            cur->child[bitI] = new Trie;
        }
        cur = cur->child[bitI];
    }

    if (accept) {
        cur->minAccept = min(queryId, cur->minAccept);
    } else {
        cur->minDeny = min(queryId, cur->minDeny);
    }
}

bool isAccept(Trie *root, ll state) {
    Trie *cur = root;
    int minAcceptSoFar = root->minAccept;
    int minDenySofar = root->minDeny;

    for (int i = 1; i <= 32; i++) {
        // left or right
        bool bitI = (state >> (32 - i)) & 1;
        if (cur->child[bitI] == NULL) {
            cur->child[bitI] = new Trie;
        }
        cur = cur->child[bitI];

        minAcceptSoFar = min(minAcceptSoFar, cur->minAccept);
        minDenySofar = min(minDenySofar, cur->minDeny);
    }

    debug(minDenySofar, minAcceptSoFar);
    //    return minAcceptSoFar <= minDenySofar;
    if (minDenySofar == INF && minAcceptSoFar == INF) {
        return true;
    }

    if (minDenySofar == INF) {
        // no deny rule
        return true;
    }

    if (minAcceptSoFar == INF) {
        // because we have deny rule, and no accept rule
        return false;
    }

    return minAcceptSoFar <= minDenySofar;
}

pair<ll, int> extract(string s) {
    int pos = s.find("/");
    ll state = 0;
    int bit = 0;
    int l = s.length();

    if (pos == s.npos) {
        // not found
        pos = l;
        bit = 32;
    } else {
        for (int j = pos + 1; j < l; ++j) {
            bit = bit * 10 + s[j] - '0';
        }
        s = s.substr(0, pos);
    }

    int curNum = 0;
    for (int i = 0; i < pos; i++) {
        if (s[i] == '.') {
            state = state * 256 + curNum;
            debug(curNum);
            curNum = 0;
        } else {
            curNum = curNum * 10 + s[i] - '0';
        }
    }
    debug(curNum);
    state = (state << 8) + curNum;
    debug(s, state, bit);
    return {state, bit};
}

int main() {
#ifdef LOCAL
    freopen("inp/F/09", "r", stdin);
    freopen("out/09.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Trie r;
    int query;
    cin >> query;
    char cmd;
    string cidr;
    REP(i, query) {
        cin >> cmd >> cidr;
        pair<ll, int> info = extract(cidr);

        if (cmd != '?') {
            update(&r, cmd == 'A', info.first, info.second, i);
        } else {
            assert(info.second == 32);
            bool ok = isAccept(&r, info.first);
            cout << (ok ? "Y" : "N") << endl;
        }
    }
}
