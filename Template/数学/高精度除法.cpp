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
