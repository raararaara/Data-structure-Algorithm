#pragma once
#include <bits/stdc++.h>
using namespace std;

/** Usage
* auto f = [](int a, int b) { return a + b; };
* sgTree<int, decltype(f)> seg(N, f, 0);
**/

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
