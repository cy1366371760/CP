const int N = 1e6 + 100;
struct PAM{  
    int tot, len[N], las, nxt[N][26], dis[N], fail[N], ocr[N];
    int dep[N];
	vector<int> ed[N]; 
	string s;
	int n; 
    void ins(int c, int ps)  
    {
        int nw = las;  
        while(ps - len[nw] - 1 < 0 || c != s[ps - len[nw] - 1] - 'a')  {
            nw = fail[nw];
        }
        if(nxt[nw][c]) {
            las = nxt[nw][c];
            ed[las].pb(ps);
            ocr[las]++;
			return; 
        }  
        int np = ++tot;  
        len[np] = len[nw] + 2;  
        int t = fail[nw];  
        while(ps - len[t] - 1 < 0 || c != s[ps - len[t] - 1] - 'a') {
            t = fail[t];  
		} 
        fail[np] = nxt[t][c];
        nxt[nw][c] = np;  
        las = np;
        ed[np].pb(ps);
        
        dep[las] = dep[fail[las]] + 1;
        ocr[las]++;
    }  
    void init(string _s, int _n)  
    {  
    	s = _s, n = _n;
        tot = 1;  
        len[1] = -1;  
        len[0] = 0;  
        dis[0] = dis[1] = 0;  
        fail[0] = 1;  
        dep[0] = dep[1] = 0;
        las = 0;
        for (int i = 0; i < n; i++) {
        	ins(s[i] - 'a', i);
		}
    } 
    void sol() {
	}
}pam;