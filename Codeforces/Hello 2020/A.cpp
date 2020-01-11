#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;
const double eps = 1e-5;
const int N = 100 + 5;

#define LOCAL
void redirect() {
    #ifdef LOCAL
        freopen("1.in","r",stdin);
        freopen("1.out","w",stdout);
    #endif
}

inline ll read() {
    ll f=1,x=0;char ch;
    do {ch=getchar(); if(ch=='-') f=-1;} while (ch<'0'||ch>'9');
    do {x=x*10+ch-'0'; ch=getchar(); } while (ch>='0'&&ch<='9');
    return x*f;
}

int n,m,q;
string a[N],b[N];

int main() {
    redirect();
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<m;i++) cin>>b[i];
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int cur; scanf("%d",&cur);
        string ans; cur -= 1;
        ans = a[cur%n] + b[cur%m];
        cout<<ans<<endl;
    }

    return 0;
}

/*
-----------------
author:dragon_bra
-----------------
*/