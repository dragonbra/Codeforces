#include<iostream>
#include<algorithm>
using namespace std;
string div(string a,int b)//�߾���a���Ե�����b
{
    string r,ans;
    int d=0;
    if(a=="0") return a;//����
    for(int i=0;i<a.size();i++)
    {
            r+=(d*10+a[i]-'0')/b+'0';//�����
            d=(d*10+(a[i]-'0'))%b;//�������
    }
    int p=0;
    for(int i=0;i<r.size();i++)
    if(r[i]!='0') {p=i;break;}
    return r.substr(p);
}
string mul(string a,string b)//�߾��ȳ˷�a,b,��Ϊ�Ǹ�����
{
    string s;
    int na[L],nb[L],nc[L],La=a.size(),Lb=b.size(); //na�洢��������nb�洢������nc�洢��
    fill(na,na+L,0); fill(nb,nb+L,0); fill(nc,nc+L,0); //��na,nb,nc����Ϊ0
    
    for(int i=La-1;i>=0;i--) na[La-i]=a[i]-'0';//���ַ�����ʾ�Ĵ�������ת��i���������ʾ�Ĵ�������
    for(int i=Lb-1;i>=0;i--) nb[Lb-i]=b[i]-'0';
    
    for(int i=1;i<=La;i++)
        for(int j=1;j<=Lb;j++)
        nc[i+j-1]+=na[i]*nb[j]; //a�ĵ�iλ����b�ĵ�jλΪ���ĵ�i+j-1λ���Ȳ����ǽ�λ��
        
    for(int i=1;i<=La+Lb;i++)
        nc[i+1]+=nc[i]/10,nc[i]%=10;//ͳһ�����λ
        
    if(nc[La+Lb]) s+=nc[La+Lb]+'0';//�жϵ�i+jλ�ϵ������ǲ���0
    
    for(int i=La+Lb-1;i>=1;i--)
        s+=nc[i]+'0';//����������ת���ַ���
    return s;
}
int main()
{
    string a;
    int b;
    while(cin>>a>>b)
    {
        cout<<div(a,b)<<endl;
    }
    return 0;
}
