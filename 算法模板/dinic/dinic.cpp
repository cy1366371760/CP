const int s = 205, t = 206;
int num = 0, ans = 0;
int head[N], cur[N], deep[N], nxt[N], las[N], to[N], cnt;
bool bfs()//�Ҳ������罨�ֲ�ͼ(����ȥ�ܸ߶���ʵ���Ǵ�Դ�㿪ʼbfs���ĵ�һ��"bfs��"..)
{   
    int now;queue<int>q;
    memset(deep,0,sizeof deep);
    deep[s]=1;
    q.push(s);
    while(!q.empty())
    {
        now=q.front();q.pop();
        for(int i=head[now];i!=-1;i=nxt[i])
        {
            if(!deep[to[i]]&&las[i])deep[to[i]]=deep[now]+1,q.push(to[i]);
        }
    }
    return deep[t];
}
int dfs(int pos,int flow)//����
{
    if(pos==t)return flow;
    for(int &i=cur[pos];i!=-1;i=nxt[i])//һ���е�ǰ���Ż��Ķ���,���ͳ���,ԭ��̫��.
    {
        if(deep[to[i]]==deep[pos]+1&&las[i])
        {
            int now=dfs(to[i],min(flow,las[i]));
            if(now)
            {
                las[i]-=now;
                las[i^1]+=now;
                return now;
            }
        }
    }   
    return 0;
}
void add_edge(int u,int v,int w)//�ӱ�
{
    nxt[++cnt]=head[u], las[cnt]=w, to[cnt]=v, head[u]=cnt;
    nxt[++cnt]=head[v], las[cnt]=0, to[cnt]=u, head[v]=cnt;
}
inline void init()
{
    memset(nxt,-1,sizeof nxt);
    memset(head,-1,sizeof head);
    cnt = -1;
    return;
}
