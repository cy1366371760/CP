int love[MAXN][MAXN];  
int ex_girl[MAXN];    
int ex_boy[MAXN];     
bool vis_girl[MAXN]; 
bool vis_boy[MAXN];   
int match[MAXN];      
int slack[MAXN];     
int N;  
bool dfs(int girl)  {  
    vis_girl[girl] = 1;  
    for (int boy = 0; boy < N; ++boy) {  
        if (vis_boy[boy]) continue; 
        int gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];  
        if (gap == 0) {    
            vis_boy[boy] = 1;  
            if (match[boy] == -1 || dfs( match[boy] )) {  
                match[boy] = girl;  
                return 1;  
            }  
        } else {  
            slack[boy] = min(slack[boy], gap); 
        }  
    }  
    return 0;  
}  
int KM()  
{  
    memset(match, -1, sizeof match);  
    memset(ex_boy, 0, sizeof ex_boy);  
    for (int i = 0; i < N; ++i) {  
        ex_girl[i] = love[i][0];  
        for (int j = 1; j < N; ++j) {  
            ex_girl[i] = max(ex_girl[i], love[i][j]);  
        }  
    }  
    for (int i = 0; i < N; ++i) {  
    
        fill(slack, slack + N, INF);   
    
        while (1) {  
            memset(vis_girl, false, sizeof vis_girl);  
            memset(vis_boy, false, sizeof vis_boy);  
    
            if (dfs(i)) break;  // 找到归宿 退出  
            int d = INF;  
            for (int j = 0; j < N; ++j)  
                if (!vis_boy[j]) d = min(d, slack[j]);  
    
            for (int j = 0; j < N; ++j) {  
                if (vis_girl[j]) ex_girl[j] -= d;  
                if (vis_boy[j]) ex_boy[j] += d;  
                else slack[j] -= d;  
            }  
        }  
    }  
    int res = 0;  
    for (int i = 0; i < N; ++i)  
        res += love[ match[i] ][i];  
    return res;  
}  
