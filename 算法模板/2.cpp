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
		int j=i,k=i+1;//��ʼ��
		while(k<=n&&s[j]<=s[k])
		{
			if(s[j]<s[k])j=i;//�ϲ�Ϊһ����
			else j++;//����ѭ������ʽ
			k++;
		}
		while(i<=j)//��v�Ŀ�ͷ���¿�ʼ
		{
			ans^=i+k-j-1;
			//cout << i + k - j - 1 << '\n';
			i+=k-j;
		}
	}
	printf("%d\n",ans);
	return 0;
}
