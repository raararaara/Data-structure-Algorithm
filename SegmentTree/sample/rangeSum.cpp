/* https://www.acmicpc.net/problem/2042 */

#include<bits/stdc++.h>

using namespace std;
using lint = long long;

const int mxn = 200020;

int N, M, Q;
lint a[mxn], b[mxn];

template<typename T, typename F>
template<typename T_Node, typename F>
struct SegTree {
    int N{}, base{};
    vector<T_Node> tree;
    const F f;
    const T_Node I;

    SegTree() = default;

    SegTree(int n, F _f, const T_Node &I) : N(n), f(_f), I(I) {
        for (base = 1; base < N; base <<= 1);
        tree.resize(base * 2 + 1, I);
    }

    T_Node get(int i) { return tree[i + base]; }

    void set(int i, T_Node v) { tree[i + base] = v; }

    void upd(int i, T_Node v) {
        tree[i += base] = v;
        while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    T_Node qry(int l, int r) {
        T_Node retL = I, retR = I;
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
        cin >> N >> M >> Q;
        Q += M;
        auto f = [](lint a, lint b) { return a + b; };
        segTree<lint, decltype(f)> seg(N, f, 0);

        for (int i = 0; i < N; i++) {
            lint x;
            cin >> x;
            seg.upd(i, x);
        }

        while (Q--) {
            int op;
            lint x, y;
            cin >> op >> x >> y;
            --x;
            if(op == 1) seg.upd(int(x), y);
            else cout << seg.qry(int(x), int(--y)) << '\n';
        }
    }

    return 0;
}
