const int Hash_mod = 1e7 + 100;
struct Hash_table {
	vector<int> buk[Hash_mod];
	void ins(int x) {
		buk[x % Hash_mod].pb(x);
	}
	int find(int x) {
		int wh = x % Hash_mod;
		for (int i = buk[wh].size() - 1; i >= 0; i--) {
			if (buk[wh][i] == x) {
				return i;
			}
		} 
		return -1;
	}
	void del(int x, int i) {
		int wh = x % Hash_mod;
		if (i == buk[wh].size() - 1) buk[wh].pop_back();
		else buk[wh].erase(buk[wh].begin() + i);
	}
}hsh_T;