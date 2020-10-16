#include <bits/stdc++.h>
using namespace std;
const int mxn = 100010, mxc = 26;

namespace aho {
	int ctoi(char c) { return c - 'a'; };
	int trie[mxn][mxc], idx, fail[mxn], term[mxn];

	void init(vector<string>&ts) {
		idx = 0;
		memset(trie, 0, sizeof trie);
		memset(fail, 0, sizeof fail);
		memset(term, 0, sizeof term);
		for (auto &t : ts) {  //insert
			int p = 0;
			for (auto &i : t) {
				int ch = ctoi(i);
				if (!trie[p][ch]) trie[p][ch] = ++idx;
				p = trie[p][ch];
			}
			term[p] = 1;
		}
		queue<int> q;  //get failure function
		for (int i = 0; i < mxc; i++)
			if (trie[0][i]) q.push(trie[0][i]);
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = 0; i < mxc; i++) if (trie[x][i]) {
				int p = fail[x];
				while (p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[x][i]] = p;
				term[trie[x][i]] += term[p];
				q.push(trie[x][i]);
			}
		}
	}
	int qry(char s[]) {
		int p = 0;
		for (int it = 0; s[it]; it++) {
			int ch = ctoi(s[it]);
			while (p && !trie[p][ch]) p = fail[p];
			p = trie[p][ch];
			if (term[p]) return 1;
		} return 0;
	}
}
