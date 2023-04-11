/* https://www.acmicpc.net/problem/16993 */

#include<bits/stdc++.h>

using namespace std;

const int mxn = 200020;

int N, M, Q;
lint a[mxn], b[mxn];

struct P {
    lint tot, LL, RR, mx;
    P() {
        tot = 0;
        LL = RR = mx = inf;
    }
    P(lint x): tot(x), LL(x), RR(x), mx(x) {}
    P(lint tot, lint LL, lint RR, lint mx) :tot(tot), LL(LL), RR(RR), mx(mx) {}
    P operator + (const P&rhs) {
        P ret;
        ret.tot = tot + rhs.tot;
        ret.LL = max(tot + rhs.LL, LL);
        ret.RR = max(RR + rhs.tot, rhs.RR);
        ret.mx = max({ mx, rhs.mx, RR + rhs.LL });
        return ret;
    }
    P& operator = (const P&rhs) = default;
};

template<typename T, typename F>
struct segTree {
    int N{}, base{};
    vector<T> tree;
    const F f;
    const T I;

    segTree() = default;

    segTree(int n, F _f, const T &I) : N(n), f(_f), I(I) {
        for (base = 1; base < N; base <<= 1);
        tree.resize(base * 2 + 1, I);
    }

    void build() {
        for (int i = base - 1; i; i--) {
            tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    T get(int i) { return tree[i + base]; }

    T set(int i, T v) { tree[i + base] = v; }

    void upd(int i, T v) {
        tree[i += base] = v;
        while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    T qry(int l, int r) {
        T retL = I, retR = I;
        for (l += base, r += base; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) retL = f(retL, tree[l++]);
            if (~r & 1) retR = f(tree[r--], retR);
        }
        return f(retL, retR);
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;
//    cin >> T;

    while (T--) {
        cin >> N;
        auto f = [](P a, P b) { return a + b; };
        segTree<P, decltype(f)> seg(N, f, P());

        for (int i = 0; i < N; i++) {
            lint x;
            cin >> x;
            seg.upd(i, P(x));
        }
        cin >> Q;

        while (Q--) {
            int l, r;
            cin >> l >> r;
            cout << seg.qry(--l, --r).mx << '\n';
        }
    }

    return 0;
}
