#include <bits/stdc++.h>
using namespace std;

const int mxn = 1818, INF = 1e9 + 7;
int N, M, C, sr, sc;

namespace flow {
	struct edge {
		int u, r, c, f;
		edge() {}
		edge(int u, int r, int c, int f = 0) :u(u), r(r), c(c), f(f) {}
		inline int residual() { return c - f; }
	};
	vector<edge> adj[mxn];
	int S, T, lv[mxn], vis[mxn];
	bitset<mxn> viss;
	inline void addedge(int u, int v, int c) {
		edge e1(v, adj[v].size(), c);
		edge e2(u, adj[u].size(), c);
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}
	void init(int id) {
		memset(vis, 0, sizeof vis);
		memset(lv, 0, sizeof lv);

	}
	int bfs() {
		memset(lv, 0, sizeof lv);
		queue<int> q;
		q.push(S);
		lv[S] = 1;
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto&e : adj[cur]) {
				int nxt = e.u;
				if (e.residual() > 0 && !lv[nxt]) {
					lv[nxt] = lv[cur] + 1;
					if (nxt != T) q.push(nxt);
				}
			}
		}
		return lv[T];
	}
	int dfs(int cur, int flow) {
		if (cur == T) return flow;
		int sz = (int)adj[cur].size();
		for (int&i = vis[cur]; i < sz; i++) {
			edge &e = adj[cur][i];
			int nxt = e.u;
			if (e.residual() > 0 && lv[nxt] == lv[cur] + 1) {
				int ret = dfs(nxt, min(e.residual(), flow));
				if (ret > 0) {
					e.f += ret;
					adj[nxt][e.r].f -= ret;
					return ret;
				}
			}
		}
		return 0;
	}
	int dinic() {
		int ret = 0, fl;
		while (bfs()) {
			memset(vis, 0, sizeof vis);
			while (fl = dfs(S, INF)) ret += fl;
		}
		return ret;
	}
	void getAB() {    // 0 for T sets, 1 for S sets
		viss.reset();
		queue<int> q;
		viss[S] = 1;
		q.push(S);
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto&it : adj[cur]) {
				if (!viss[it.u] && it.residual() > 0) {
					viss[it.u] = 1;
					q.push(it.u);
				}
			}
		}
		for (int i = 1; i <= N; i++)
			if (viss[i]) cout << i << ' ';
		cout << '\n';
		for (int i = 1; i <= N; i++)
			if (!viss[i]) cout << i << ' ';
		cout << '\n';
	}
}
