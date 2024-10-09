#include<bits/stdc++.h>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[5000005];
int n,ans;
int main()
{
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for(int i=1;i<=n;)
	{
		int j=i,k=i+1;//初始化
		while(k<=n&&s[j]<=s[k])
		{
			if(s[j]<s[k])j=i;//合并为一整个
			else j++;//保持循环不变式
			k++;
		}
		while(i<=j)//从v的开头重新开始
		{
			ans^=i+k-j-1;
			//cout << i + k - j - 1 << '\n';
			i+=k-j;
		}
	}
	printf("%d\n",ans);
	return 0;
}
