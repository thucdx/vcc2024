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

const int MAX_N = 5;

bool lose[MAX_N][MAX_N][MAX_N][MAX_N][MAX_N];
int count[MAX_N][MAX_N][MAX_N][MAX_N][MAX_N];

struct Move {
    int f[5];

    Move(int _f[5]) {
        REP(i, 5) f[i] = _f[i];
    }
};

bool operator<(const Move& a, const Move & b) {
    REP(i, 5) {
        if (a.f[i] != b.f[i]) {
            return a.f[i] < b.f[i];
        }
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("inp/H1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    lose[0][0][0][0][0] = true;

    vector<Move> moves = {
            // 1
            Move(new int[5]{1, 0, 0, 0, 0}),
            Move(new int[5]{0, 1, 0, 0, 0}),
            Move(new int[5]{0, 0, 1, 0, 0}),
            Move(new int[5]{0, 0, 0, 1, 0}),
            Move(new int[5]{0, 0, 0, 0, 1}),
            // 3
            Move(new int[5]{1, 1, 1, 0, 0}),
            Move(new int[5]{0, 1, 1, 1, 0}),
            Move(new int[5]{0, 0, 1, 1, 1}),
            // 5
            Move(new int[5]{1, 1, 1, 1, 1})
    };

    int id[6];
    int cnt = 0;
    set<Move> sol;
    for (id[1] = 0; id[1] < MAX_N; id[1]++)
        for (id[2] = 0; id[2] < MAX_N; id[2]++)
            for (id[3] = 0; id[3] < MAX_N; id[3]++)
                for (id[4] = 0; id[4] < MAX_N; id[4]++)
                    for (id[5] = 0; id[5] < MAX_N; id[5]++) {
                        bool &cur = lose[id[1]][id[2]][id[3]][id[4]][id[5]];
                        cur = true;
                        bool allWin = true;
                        EACH(move, moves) {
                            bool isOK = true;
                            int minVal = 2 * MAX_N;
                            REP(i, 5) {
                                if (move.f[i] > 0) {
                                    if (id[1 + i] == 0) {
                                        isOK = false;
                                        break;
                                    }
                                    minVal = min(id[1 + i], minVal);
                                }
                            }

                            if (!isOK) continue;
//                            debug(minVal);
                            FOR(i, 1, minVal) {
                                int ni1 = move.f[0] > 0 ? id[1] - i : id[1];
                                int ni2 = move.f[1] > 0 ? id[2] - i : id[2];
                                int ni3 = move.f[2] > 0 ? id[3] - i : id[3];
                                int ni4 = move.f[3] > 0 ? id[4] - i : id[4];
                                int ni5 = move.f[4] > 0 ? id[5] - i : id[5];

                                allWin &= !lose[ni1][ni2][ni3][ni4][ni5];
                           }
                        }

                        if (allWin) {
                            // sure lose
                            cur = true;
                        } else {
                            cur = false;
                        }

                        if (cur) {
                            FOR(i, 1, 5) {
                                cout << id[i] << " ";
                            }
                            cout << endl;
                            cnt++;
                            sol.insert(Move(new int[5]{id[1], id[2], id[3], id[4], id[5]}));
                            debug(id[1], id[2], id[3], id[4], id[5], cur);
                        }
                    }

    cout << cnt << endl;
    set<Move> all;
    REP(i1, MAX_N) {
        REP(i2, MAX_N) {
            REP(i3, MAX_N) {
                REP(i4, MAX_N) {
                    REP(i5, MAX_N) {
                        if ((i1 ^ i2 ^ i3 ^ i4 ^ i5) == 0) {
                            all.insert(Move(new int[5] {i1, i2, i3, i4, i5}));
                        }
                    }
                }
            }
        }
    }

    debug(SZ(all), SZ(sol));
    // Check if
    EACH(e, all) {
        if (sol.count(e) == 0) {
            cout << "not in: " << e.f[0] << " " << e.f[1] << " " << e.f[2] << " " << e.f[3] << " " << e.f[4] << endl;
        }
    }

}