#include <cstring>

constexpr char basis = 'a';
const int alphabets = 26;

inline constexpr int ctoi(char c) { return c - basis; };

struct TrieNode {
	bool terminal;
	TrieNode* child[alphabets];
	TrieNode() : terminal(false) {
		memset(child, 0, sizeof(child));
	}
	~TrieNode() {
		for (int i = 0; i < alphabets; i++)
			delete child[i];
	}

	void insert(const char* key) {
		if (*key == 0) {
			terminal = true;
		}
		else {
			int next = ctoi(*key);

			if (child[next] == 0)
				child[next] = new TrieNode();

			child[next]->insert(key + 1);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = ctoi(*key);
		if (child[next] == 0) return 0;
		return child[next]->find(key + 1);
	}
};