#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;   //�ַ����������ֵ

char s[maxn];
int _next[maxn],ex[maxn]; //ex���鼴Ϊextend����
//Ԥ�������__next����

void GET_next(char *str)
{
    int i=0,j,po,len=strlen(str);
    _next[0]=len;//��ʼ��_next[0]
    while(str[i]==str[i+1]&&i+1<len)//����_next[1]
    i++;
    _next[1]=i;
    po=1;//��ʼ��po��λ��
    for(i=2;i<len;i++)
    {
        if(_next[i-po]+i<_next[po]+po)//��һ�����������ֱ�ӵõ�_next[i]��ֵ
        _next[i]=_next[i-po];
        else//�ڶ��������Ҫ����ƥ����ܵõ�_next[i]��ֵ
        {
            j=_next[po]+po-i;
            if(j<0)j=0;//���i>po+_next[po],��Ҫ��ͷ��ʼƥ��
            while(i+j<len&&str[j]==str[j+i])//����_next[i]
            j++;
            _next[i]=j;
            po=i;//����po��λ��
        }
    }
}

//����extend����
void EXKMP(char *s1,char *s2)
{
    int i=0,j,po,len=strlen(s1),l2=strlen(s2);
    GET_next(s2);//�����Ӵ���_next����
    while(s1[i]==s2[i]&&i<l2&&i<len)//����ex[0]
    i++;
    ex[0]=i;
    po=0;//��ʼ��po��λ��
    for(i=1;i<len;i++)
    {
        if(_next[i-po]+i<ex[po]+po)//��һ�������ֱ�ӿ��Եõ�ex[i]��ֵ
        ex[i]=_next[i-po];
        else//�ڶ��������Ҫ����ƥ����ܵõ�ex[i]��ֵ
        {
            j=ex[po]+po-i;
            if(j<0)j=0;//���i>ex[po]+po��Ҫ��ͷ��ʼƥ��
            while(i+j<len&&j<l2&&s1[j+i]==s2[j])//����ex[i]
            j++;
            ex[i]=j;
            po=i;//����po��λ��
        }
    }
}

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%s",s);
		EXKMP(s,s);
		int len=strlen(s);ll cnt=len-1;
		//for(int i=1;i<len;i++) cout<<ex[i]<<' ';cout<<endl;
		for(int i=len-1;i>0;i--){
			if(ex[i]!=0&&(i+ex[i]==len)){
				cnt+=ex[i];cnt-=1;
			}
			else cnt+=ex[i];
		}
		printf("%lld\n",cnt);
	}
	return 0;
}
