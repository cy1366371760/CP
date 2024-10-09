struct Bignum {
	vector<int> val;
	int len;
	Bignum(){};
	Bignum(string s) {
		len = s.length();
		val.resize(len);
		for (int i = 0; i < len; i++) {
			assert(s[i] >= '0' && s[i] <= '9');
			val[i] = s[i] - '0';
		}
		reverse(all(val));
	}
	bool operator <(Bignum b) {
		if (len < b.len) return 1;
		if (len > b.len) return 0;
		for (int i = len - 1; i >= 0; i--) {
			if (val[i] != b.val[i]) return val[i] < b.val[i];
		}
		return 0;
	}
	bool operator ==(Bignum b) {
		if (len != b.len) return 0;
		for (int i = len - 1; i >= 0; i--) {
			if (val[i] != b.val[i]) return 0;
		}
		return 1;
	}
	Bignum operator +(Bignum b) {
		Bignum res;
		int n = max(len, b.len);
		int carry = 0;
		
		res.val.resize(len);
		val.resize(len);
		b.val.resize(len);
		
		for (int i = 0; i < n; i++) {
			int nw = val[i] + b.val[i] + carry;
			res.val[i] = nw % 10;
			carry = nw / 10;
		}
		if (carry) res.val.pb(carry);
		res.len = res.val.size();
		return res;
	}
	Bignum operator -(Bignum b) {
		assert(b < *this || b == *this);
		Bignum res;
		int n = max(len, b.len);
		int carry = 0;
		
		res.val.resize(len);
		val.resize(len);
		b.val.resize(len);
		
		for (int i = 0; i < n; i++) {
			int nw = val[i] - b.val[i] - carry;
			if (nw < 0) {
				carry = 1;
				res.val[i] = nw + 10;
			} else {
				carry = 0;
				res.val[i] = nw;
			}
		}
		assert(!carry);
		while (!res.val.empty() && res.val.back() == 0)res.val.pop_back();
		res.len = res.val.size();
		return res;
	}
	string to_string() {
		string res = "";
		if (len == 0) {
			res += '0';
			return res;
		}
		for (int i = len - 1; i >= 0; i--) {
			res += (char)(val[i] + '0');
		}
		return res;
	}
};