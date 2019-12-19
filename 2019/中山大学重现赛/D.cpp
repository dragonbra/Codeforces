#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
 
 
int n,m;
int a[maxn],b[maxn];
int f[maxn][20];//f[i][j]��ʾ��iλ���2^j�����е����������[i,i+(1<<j)-1]
int df[maxn][20];
 
 
void ST_prewoek()
{
	for(int i=1;i<=n;i++) f[i][0]=a[i];
	for(int i=1,imax=log2(n);i<=imax;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)//ע��j���Ҷ˵�Ϊj+(1<<i)-1��-1����ΪҪ����j�Լ� 
			f[j][i]=max(f[j][i-1],f[j+(1<<i-1)][i-1]);
}

void ST_prewoek_2()
{
	for(int i=1;i<=n;i++) df[i][0]=b[i];
	for(int i=1,imax=log2(n);i<=imax;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)//ע��j���Ҷ˵�Ϊj+(1<<i)-1��-1����ΪҪ����j�Լ� 
			df[j][i]=min(df[j][i-1],df[j+(1<<i-1)][i-1]);
}
 
 
int ST_query(int l,int r)//��[l,r]�е����ֵ 
{
	int k=log2(r-l+1);//���䳤��r-l+1 
	return max(f[l][k],f[r-(1<<k)+1][k]);//��1�����䣺[l,l+(1<<k)-1]����2�����䣺[r,(1<<k)+1~r]
}

int ST_query(int l,int r)//��[l,r]�е����ֵ 
{
	int k=log2(r-l+1);//���䳤��r-l+1 
	return min(f[l][k],f[r-(1<<k)+1][k]);//��1�����䣺[l,l+(1<<k)-1]����2�����䣺[r,(1<<k)+1~r]
}


 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	ST_prewoek();
	ST_prewoek_2();
	while(m--)
	{
		int l,r,ans;
		scanf("%d%d",&l,&r);
		ans=ST_query(l,r);
		printf("%d\n",ans);
	}
	return 0;
}
